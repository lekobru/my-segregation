﻿float Shot_Time;


void __stdcall Event_Processor(void* Event)
{
	void* Local_Player = *(void**)607867332;
	char* KillSay[] = {
	"noob"
	};
	if (Local_Player != nullptr)
	{
		using Get_Name_Type = char*(__thiscall*)(void* Event);

		char* Name = Get_Name_Type(537579280)(Event);

		using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

		using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Local_Number = *(__int32*)((unsigned __int32)Local_Player + 80);



		if (Name[0] == 'p')
		{
			__int32 Victim_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));

			__int32 Killer_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"attacker", nullptr));

			if (Killer_Number == Local_Number)
			{
				// Verificar si Kill_Say est� activado antes de enviar el mensaje
				if (Interface_Kill_Say.Integer == 1)
				{
					// Solo env�a un mensaje de Kill_Say cuando el jugador local realiza el asesinato
					char killMessage[256];
					sprintf(killMessage, "say %s", KillSay[0]);
					using Client_Cmd_Type = void(__thiscall*)(void*, char*);
					Client_Cmd_Type(537018048)((void*)540435380, killMessage);
				}
			}

			if (Victim_Number != Killer_Number)
			{
				if (Killer_Number != 0)
				{
					if (Victim_Number == Local_Number)
					{
						if (Name[7] == 'd')
						{
							Player_Data_Structure* Player_Data = &Players_Data[Killer_Number];

							Player_Data->Memory_Tolerance = 0;
						}
					}
					else
					{
						if (Killer_Number == Local_Number)
						{
							if (Victim_Number == Recent_Player_Data_Number)
							{
								__int8 Revert = 1;

								Player_Data_Structure* Player_Data = &Players_Data[Victim_Number];

								if (Name[7] == 'h')
								{
									if (Interface_Aim_Intersection.Integer == 0)
									{
										Revert = Get_Integer_Type(537579136)(Event, (char*)"hitgroup", nullptr);
									}

									if (Revert == 1)
									{
										if (Player_Data->Memory_Tolerance == 0)
										{
											if (Player_Data->Tolerance == Interface_Bruteforce_Tolerance.Integer)
											{
												Player_Data->Shots_Fired = ((Player_Data->Shots_Fired - 1) % Bruteforce_Angles_Count + Bruteforce_Angles_Count) % Bruteforce_Angles_Count;
											}
											else
											{
												Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
											}
										}
									}
								}
								else
								{
									if (Interface_Bruteforce_Memory_Tolerance.Integer != 0)
									{
										if (Interface_Aim_Intersection.Integer == 0)
										{
											Revert = Get_Integer_Type(537579136)(Event, (char*)"headshot", nullptr);
										}

										if (Revert == 1)
										{
											if (Player_Data->Memory_Tolerance == 0)
											{
												Player_Data->Tolerance = 0;

												Player_Data->Memorized_Y = Bruteforce_Angles[Player_Data->Shots_Fired];
											}

											Player_Data->Memory_Tolerance = Interface_Bruteforce_Memory_Tolerance.Integer;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			Shot_Time *= Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr)) != Local_Number;
		}
	}
}