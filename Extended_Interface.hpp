struct Interface_Structure
{
	__int8 Additional_Bytes_1[32];

	char* String;

	__int8 Additional_Bytes_2[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_3[24];
};

Interface_Structure Interface_Commentator;

Interface_Structure Interface_Get_Priorities;

#include "Priority.hpp"

Interface_Structure Interface_Set_Priority;

Interface_Structure Interface_Bruteforce_Memory_Tolerance;

Interface_Structure Interface_Bruteforce_Tolerance;

#include "Bruteforce.hpp"

Interface_Structure Interface_Bruteforce;

Interface_Structure Interface_Bruteforce_Angles;

Interface_Structure Interface_Alternative;

Interface_Structure Interface_Minimum_Choked_Commands;

Interface_Structure Interface_Maximum_Choked_Commands;

Interface_Structure Interface_Aim_Intersection;

Interface_Structure Interface_Aim_Height;

Interface_Structure Interface_Angle_X;

Interface_Structure Interface_First_Choked_Angle_Y;

Interface_Structure Interface_Second_Choked_Angle_Y;

Interface_Structure Interface_Angle_Y;

Interface_Structure Interface_Uber_Alles_Scale;

Interface_Structure Interface_Uber_Alles_Speed;

Interface_Structure Interface_Simulation_Height;

Interface_Structure Interface_Simulation_Ticks;

Interface_Structure Interface_Simulation_Rotation_Divisor;

Interface_Structure Interface_Jitter_Range;

Interface_Structure Interface_At_Targets;

Interface_Structure Interface_Chams;

Interface_Structure Interface_Extrapolation;

Interface_Structure Interface_Enemy_Check;

void Implement_Extended_Interface()
{
	auto Create_Interface = [](Interface_Structure* Interface, char* Name, char* Value, void* Handler)
		{
			if (Value == nullptr)
			{
				using Create_Command_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

				Create_Command_Type(606174864)(Interface, Name, Handler, nullptr, nullptr, nullptr);
			}
			else
			{
				using Create_Variable_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

				Create_Variable_Type(539131040)(Interface, Name, Value, nullptr, nullptr, Handler);
			}

			wprintf(L"[ + ] %hs -> %p\n", Name, Interface);
		};

#define Pointer_Name(Interface) &Interface, (char*)#Interface + 10

	Create_Interface(Pointer_Name(Interface_Commentator), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Get_Priorities), nullptr, (void*)Get_Priorities);

	Create_Interface(Pointer_Name(Interface_Set_Priority), (char*)"1 0", (void*)Set_Priority);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Memory_Tolerance), (char*)"1", (void*)Bruteforce_Reset_Memory_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Tolerance), (char*)"1", (void*)Bruteforce_Reset_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce), (char*)"1", (void*)Bruteforce_Reset);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Angles), (char*)"0, -90, 90", (void*)Bruteforce_Set_Angles);

	Bruteforce_Set_Angles(&Interface_Bruteforce_Angles);

	Create_Interface(Pointer_Name(Interface_Alternative), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Minimum_Choked_Commands), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Maximum_Choked_Commands), (char*)"21", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Intersection), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Height), (char*)"0.9", nullptr);

	Create_Interface(Pointer_Name(Interface_Angle_X), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_First_Choked_Angle_Y), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_Second_Choked_Angle_Y), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_Angle_Y), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Scale), (char*)"16", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Speed), (char*)"192", nullptr);

	Create_Interface(Pointer_Name(Interface_Simulation_Height), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Simulation_Ticks), (char*)"32", nullptr);

	Create_Interface(Pointer_Name(Interface_Simulation_Rotation_Divisor), (char*)"90", nullptr);

	Create_Interface(Pointer_Name(Interface_Jitter_Range), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_At_Targets), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Chams), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Extrapolation), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Enemy_Check), (char*)"1", nullptr);
}