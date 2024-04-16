#pragma once

#include "vmt.hpp"

#include "interfaces.hpp"

#include "global_utils.hpp"

#include "matrix.hpp"


bool world2screen(const vec3_t& pos, vec3_t& output)
{
	VMatrix matrix = *(VMatrix*)(*(int(__thiscall**)(DWORD))(**(DWORD***)540447280 + 15))(*(DWORD*)540447280); // *(VMatrix*)540447280;

	output.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	output.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

	float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

	if (w < 0.01f)
		return false;

	float inv_w = 1.0f / w;

	output.x *= inv_w;
	output.y *= inv_w;

	using Get_Screen_Size_Type = __int32(__cdecl*)();

	int True_Screen_Width = Get_Screen_Size_Type(604542880)();

	int True_Screen_Height = Get_Screen_Size_Type(604542848)();


	float x = (float)(True_Screen_Width / 2);
	float y = (float)(True_Screen_Height / 2);


	x += 0.5f * output.x * True_Screen_Width + 0.5f;
	y -= 0.5f * output.y * True_Screen_Height + 0.5f;

	output.x = x;
	output.y = y;

	return true;
}




const char* get_panel_name(unsigned int vgui_panel)
{
	typedef const char*(__thiscall* o_fn)(void*, unsigned int);
	return global_utils::v_function<o_fn>(interfaces::vgui_ipanel, 35)(interfaces::vgui_ipanel, vgui_panel);
}




void draw_esp()
{
	void* Local_Player = *(void**)607867332;

	if (!Local_Player)
		return;

	if (*(__int8*)((unsigned __int32)Local_Player + 135) != 0)
		return;

	void* Surface = *(void**)608279384;

	using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

	using Draw_Filled_Rect_Type = void(__thiscall**)(void* Surface, int x01, int y01, int x02, int y02);
	using Draw_OutLined_Rect_Type = void(__thiscall**)(void* Surface, int x01, int y01, int x02, int y02);

	for (int Entity_Number = 0; Entity_Number < 64; ++Entity_Number)
	{
		void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

		if (!Entity || *(__int8*)((unsigned __int32)Entity + 135) != 0)
			continue;

		if (*(__int32*)((unsigned __int32)Entity + 144) == *(__int32*)((unsigned __int32)Local_Player + 144))
			continue;

		//if (*(__int8*)((unsigned __int32)Entity + 320) != 0)
			//continue;


		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		if (!Player_Data)
			continue;

		__int32 health = *reinterpret_cast<__int32*>((unsigned __int32)Entity + 3492);

		if (health <= 0 || health > 150)
			continue;


		if (Entity && Entity != Local_Player)
		{
			vec3_t* Entity_Origin = reinterpret_cast<vec3_t*>((unsigned __int32)Entity + 668);

			vec3_t bottom_position, top_position;

			vec3_t copy = *Entity_Origin;

			if (!world2screen(*Entity_Origin, bottom_position) || !world2screen(copy + vec3_t(0, 0, 72), top_position))
				continue;

			float height = bottom_position.y - top_position.y;
			float half_width = height * .31f;

			if (health > 0)
			{
				int Scale = health * 2.55f;

				//(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);
				//(*Draw_OutLined_Rect_Type(*(unsigned __int32*)Surface + 60))(Surface, top_position.x - half_width - 7, top_position.y - 1, top_position.x - half_width - 7 + 5, top_position.y - 1 + (height + 2));

				(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, (255 - Scale), Scale, 0, 255);
				(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width - 6, top_position.y, top_position.x - half_width - 6 + 1, top_position.y + height);

				(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, (255 - Scale), Scale, 0, 255);
				(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width - 5, top_position.y, top_position.x - half_width - 6 + 1, top_position.y + height);

				(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, (255 - Scale), Scale, 0, 255);
				(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width - 4, top_position.y, top_position.x - half_width - 6 + 1, top_position.y + height);

				//(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);
				//(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width - 6, top_position.y, top_position.x - half_width - 6 + 3, top_position.y + ((100 - health) * (height / 100)));
			}

			(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 255, 255, 255, 255);

			(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width, top_position.y, bottom_position.x + half_width, bottom_position.y);

			(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 255, 255, 255, 255);

			(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width, top_position.y, bottom_position.x + half_width, bottom_position.y);

			(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);

			(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width - 1, top_position.y - 1, bottom_position.x + half_width + 1, bottom_position.y + 1);

			(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);

			(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, top_position.x - half_width + 1, top_position.y + 1, bottom_position.x + half_width - 1, bottom_position.y - 1);
		}
	}
}


typedef void(__thiscall* paint_traverse_t) (void*, unsigned int, bool, bool);

void __thiscall Redirected_Paint_Traverse(void* thisptr, unsigned int vgui_panel, bool force_repaint, bool allow_force)
{
	static auto o_paint_traverse = panel_hook->get_original<paint_traverse_t>(40);

	o_paint_traverse(thisptr, vgui_panel, force_repaint, allow_force);


	const char* panel_name = get_panel_name(vgui_panel);

	if (panel_name && panel_name[0] == 'M' && panel_name[3] == 'S' && panel_name[9] == 'T') {
		draw_esp(); //# draw esp
	}
}

void* Create_Material(__int8 shouldIgnoreZ, __int8 isLit, __int8 isWireframe) {
	static __int32 Created = 0;

	static std::string Tmp{
		"\"%s\"\
        \n{\
        \n\t\"$basetexture\" \"vgui/white_additive\"\
        \n\t\"$envmap\" \"\"\
        \n\t\"$model\" \"1\"\
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
	sprintf(Material, Tmp.c_str(), "VertexLitGeneric", (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char Name[512];
	sprintf(Name, "#Error_Chams%i.vmt", Created);
	++Created;

	void* Key_Values = malloc(0x24);

	using Key_Values_Type = void(__thiscall*)(void* Key_Values, char* Name);
	Key_Values_Type(0x20222360)(Key_Values, "VertexLitGeneric");

	using Load_From_Buffer_Type = __int8(__thiscall*)(void* Key_Values, char*, char*, void*, char*);
	Load_From_Buffer_Type(0x202250C0)(Key_Values, Name, Material, nullptr, nullptr);

	using Create_Material_Type = void* (__thiscall*)(void* Material_System, char* Name, void* Key_Values);
	void* Created_Material = Create_Material_Type(*(DWORD*)(**(DWORD**)0x24419508 + 0x1EC))(*(void**)0x24419508, Name, Key_Values);

	return Created_Material;
}

void* Original_Draw_Model;

void __thiscall Draw_Model(void* Studio_Render, void* Model_Info, void* a, void* b, void* d, __int32 Unknown_Parameter_6) {
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

	if (Interface_Chams.Integer == 1 && (strstr(Model_Name, "models/player/") ))
	{
		float Color[4] = { };

		if (strstr(Model_Name, "ct_"))
		{
			// Si el modelo pertenece a los contra-terroristas, establecer el color azul para las chams
			Color[0] = 75.f * (1.0f / 255.0f);  // Rojo

			Color[1] = 208.f * (1.0f / 255.0f);    // Verde

			Color[2] = 162.f * (1.0f / 255.0f);    // Azul

			Color[3] = 75.f * (1.0f / 255.0f);  // Alpha (opacidad)
		}
		else if (strstr(Model_Name, "t_"))
		{
			// Si el modelo pertenece a los terroristas, establecer el color rojo para las chams
			Color[0] = 255.f * (1.0f / 255.0f);  // Rojo

			Color[1] = 150.f * (1.0f / 255.0f);    // Verde

			Color[2] = 255.f * (1.0f / 255.0f);    // Azul

			Color[3] = 75.f * (1.0f / 255.0f);  // Alpha (opacidad)

		}

		Set_Color_Modulation_Type(0x2C001FD0)(Studio_Render, Color);

		Forced_Material_Override_Type(0x2C007440)(Studio_Render, CoveredLit, 0);

		(decltype(&Draw_Model)(Original_Draw_Model))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

		Forced_Material_Override_Type(0x2C007440)(Studio_Render, OpenLit, 0);
	}
	else
		Forced_Material_Override_Type(0x2C007440)(Studio_Render, nullptr, 0);

	(decltype(&Draw_Model)(Original_Draw_Model))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	Forced_Material_Override_Type(0x2C007440)(Studio_Render, nullptr, 0);
}
