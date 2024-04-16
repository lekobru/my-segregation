#include <string>

#include "vmt.hpp"

#include "interfaces.hpp"

#include "global_utils.hpp"

#include "matrix.hpp"
#include <Extended_Interface.hpp>

void* Create_Material(__int8 shouldIgnoreZ, __int8 isLit, __int8 isWireframe)
{
	static __int32 Created = 0;

	static std::string Tmp
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};

	char Material[512];
	sprintf(Material, Tmp.c_str(), (isLit == 1 ? "VertexLitGeneric" : "UnlitGeneric"), (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char Name[512];
	sprintf(Name, "#Error_Chams%i.vmt", Created);
	++Created;

	void* Key_Values = malloc(0x24);

	using Key_Values_Type = void(__thiscall*)(void* Key_Values, char* Name);

	Key_Values_Type(0x20222360)(Key_Values, (char*)(isLit == 1 ? "VertexLitGeneric" : "UnlitGeneric"));

	using Load_From_Buffer_Type = __int8(__thiscall*)(void* Key_Values, char*, char*, void*, char*);

	Load_From_Buffer_Type(0x202250C0)(Key_Values, Name, Material, nullptr, nullptr);

	using Create_Material_Type = void* (__thiscall*)(void* Material_System, char* Name, void* Key_Values);

	void* Created_Material = Create_Material_Type(*(DWORD*)(**(DWORD**)0x24419508 + 0x1EC))(*(void**)0x24419508, Name, Key_Values);

	//	using Increment_Reference_Count_Type = void(__thiscall*)(void* Material);

	//	Increment_Reference_Count_Type(*(DWORD*)(**(DWORD**)Created_Material + 0x30))(Created_Material);

	//	free(Key_Values);

	return Created_Material;
}

void* Original_Draw_Model;

void __thiscall Draw_Model(void* Studio_Render, void* Model_Info, void* a, void* b, void* d, __int32 Unknown_Parameter_6)
{
	if (Interface_Chams.Integer != 1)

		static void* CoveredLit = Create_Material(true, true, false);
	static void* OpenLit = Create_Material(false, true, false);
	static void* CoveredFlat = Create_Material(true, false, false);
	static void* OpenFlat = Create_Material(false, false, false);

	void* Entity = *(void**)((unsigned __int32)Model_Info + 0x18);

	if (!Entity)
		return (decltype(&Draw_Model)(Original_Draw_Model))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	auto Model = (*(void* (__thiscall**)(void*))(*(DWORD*)Entity + 32))(Entity);

	using Get_Model_Name_Type = char* (__thiscall*)(void* Model_Info, void* Model);

	char* Model_Name = Get_Model_Name_Type(0x200F5320)(*(void**)0x243BEA84, Model);

	using Forced_Material_Override_Type = void(__thiscall*)(void* Model_Render, void* Material, __int32 Type);

	using Set_Color_Modulation_Type = void(__thiscall*)(void* Render_View, float*);

	if (strstr(Model_Name, "models/player"))
	{
		float Color[4] = { };

		Color[0] = 69.f * (1.0f / 255.0f);  // Rojo

		Color[1] = 111.f * (1.0f / 255.0f);    // Verde

		Color[2] = 154.f * (1.0f / 255.0f);    // Azul

		Color[3] = 60.f * (1.0f / 255.0f);  // Alpha (opacidad)

		static void* CoveredLit = Create_Material(true, true, false);

		Set_Color_Modulation_Type(0x2C001FD0)(Studio_Render, Color);

		Forced_Material_Override_Type(0x2C007440)(Studio_Render, CoveredLit, 0);

		(decltype(&Draw_Model)(Original_Draw_Model))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

		Color[0] = 69.f * (1.0f / 255.0f);  // Rojo

		Color[1] = 111.f * (1.0f / 255.0f);    // Verde

		Color[2] = 154.f * (1.0f / 255.0f);    // Azul

		Color[3] = 60.f * (1.0f / 255.0f);  // Alpha (opacidad)

		Set_Color_Modulation_Type(0x2C001FD0)(Studio_Render, Color);

		Forced_Material_Override_Type(0x2C007440)(Studio_Render, OpenLit, 0);
	}
	else
		Forced_Material_Override_Type(0x2C007440)(Studio_Render, nullptr, 0);

	(decltype(&Draw_Model)(Original_Draw_Model))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	Forced_Material_Override_Type(0x2C007440)(Studio_Render, nullptr, 0);
}