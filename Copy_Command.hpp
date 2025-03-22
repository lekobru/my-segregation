struct Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_2[1];

	__int32 Select;

	__int8 Additional_Bytes_3[4];

	__int32 Random_Seed;
};

double jitter(double value1, double value2) {
	static bool toggle = false;
	toggle = !toggle; // Toggle the value
	return toggle ? value1 : value2;
}
#define TIME_TO_TICKS( dt )    ( ( int )( 0.5f + ( float )( dt ) / Global_Variables->Interval_Per_Tick ) )
float M_PI = 3.14;
double deg2rad(double deg)
{
	return deg * M_PI / 180.0;
}

Player_Data_Structure Previous_Recent_Player_Data;

void* Original_Copy_Command_Caller;

void __thiscall Redirected_Copy_Command(void* Unknown_Parameter, Command_Structure* Command)
{
	void* Local_Player = *(void**)607867332;

	if (*(__int8*)((unsigned __int32)Local_Player + 135) == 0)
	{
		auto Angle_Vectors = [](float* Angles, float* Forward, float* Right, float* Up) -> void
		{
			using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

			Angle_Vectors_Type(606384752)(Angles, Forward, Right, Up);
		};

		__int32 Jump_State = (Command->Buttons & 2) + *(__int8*)((unsigned __int32)Local_Player + 308);

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1]
		};

		static float Previous_Move_Angle_Y;

		float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

		if (Jump_State == 4)
		{
			Command->Move[0] = 0;

			if (*(void**)((unsigned __int32)Local_Player + 456) == INVALID_HANDLE_VALUE)
			{
				Command->Buttons &= ~2;
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 3420) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30.f, __builtin_hypotf(Velocity[0], Velocity[1])) * 180.f / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180.f / 3.1415927f, 360.f);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -400.f;
				}
				else
				{
					Command->Move[1] = 400.f;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -400.f;
				}
				else
				{
					Command->Move[1] = 400.f;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2];

		Byte_Manager::Copy_Bytes(1, Previous_Move, sizeof(Previous_Move), Command->Move);

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0.f;

		auto Vector_Normalize = [](float* Vector) -> float
		{
			using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

			return Vector_Normalize_Type(606378096)(Vector);
		};

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0.f;

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * Command->Move[0] + Desired_Move_Right[0] * Command->Move[1],

			Desired_Move_Forward[1] * Command->Move[0] + Desired_Move_Right[1] * Command->Move[1]
		};

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

			Move_Forward[2] = 0.f;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0.f;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			Command->Move[0] = (__int16)((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider);

			Command->Buttons &= ~1560;

			if (Command->Move[0] != 0)
			{
				Command->Buttons |= 8 * (__builtin_signbitf(Command->Move[0]) + 1);
			}

			Command->Move[1] = (__int16)((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider);

			if (Command->Move[1] != 0)
			{
				Command->Buttons |= 512 * ((__builtin_signbitf(Command->Move[1]) ^ 1) + 1);
			}
		};

		Correct_Movement();

		void* Previous_Audio_Device = *(void**)542589456;

		*(void**)542589456 = nullptr;

		float Local_Previous_Origin[3];

		float* Local_Origin = (float*)((unsigned __int32)Local_Player + 668);

		if (Interface_Alternative.Integer == 0)
		{
			Byte_Manager::Copy_Bytes(1, Local_Previous_Origin, sizeof(Local_Previous_Origin), Local_Origin);
		}

		auto Predict = [&](__int8 Duck) -> void
		{
			Command->Buttons |= 4 * Duck;

			using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Player, Command_Structure* Command, void* Move_Helper);

			Run_Command_Type(605207600)((void*)608163016, Local_Player, Command, (void*)607735532);
		};

		if (Jump_State * (Interface_Duck_Advantage.Floating_Point != 0.f) == 4)
		{
			Predict(0);

			auto Restore = [&]() -> float
			{
				Command->Buttons &= ~4;

				float Speed = __builtin_hypotf(Velocity[0], Velocity[1]);

				using Run_Prediction_Type = void(__cdecl*)();

				Run_Prediction_Type(537158848)();

				return Speed;
			};

			if (*(float*)((unsigned __int32)Local_Player + 220) == 64.f)
			{
				float Normal_Speed = Restore();

				Predict(1);

				float Duck_Speed = Restore();

				Command->Buttons |= 4 * (Normal_Speed < Duck_Speed - Interface_Duck_Advantage.Floating_Point);
			}
			else
			{
				Restore();

				Command->Buttons |= 4;
			}
		}

		Predict(0);

		*(void**)542589456 = Previous_Audio_Device;

		Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

		static __int8 Send_Packet;

		__int32 Choked_Commands = *(__int32*)540627872;

		__int8 Predicted_Send_Packet = 0;

		static float Local_Networked_Origin[3];

		if (Interface_Alternative.Integer == 0)
		{
			__int32 Predicted_Choked_Commands = Choked_Commands + 1;

			if (Choked_Commands < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;

				if (Predicted_Choked_Commands == Interface_Minimum_Choked_Commands.Integer)
				{
					if (Predicted_Choked_Commands < Interface_Maximum_Choked_Commands.Integer)
					{
						goto Predict_Dynamic_Send_Packet_Label;
					}
					else
					{
						Predicted_Send_Packet = 1;
					}
				}
			}
			else
			{
				if (Choked_Commands < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_powf(Local_Networked_Origin[0] - Local_Previous_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Previous_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Previous_Origin[2], 2.f) <= 4096.f)
					{
						Send_Packet = 0;

						Predict_Dynamic_Send_Packet_Label:
						{
							if (Predicted_Choked_Commands == Interface_Maximum_Choked_Commands.Integer)
							{
								Predicted_Send_Packet = 1;
							}
							else
							{
								if (__builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) > 4096.f)
								{
									Predicted_Send_Packet = 1;
								}
							}
						}

					}
					else
					{
						Send_Packet_Label:
						{
							Byte_Manager::Copy_Bytes(1, Local_Networked_Origin, sizeof(Local_Networked_Origin), Local_Origin);

							Send_Packet = 1;
						}
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}
		else
		{
			if (Send_Packet == 2)
			{
				goto Send_Packet_Label;
			}

			if (Choked_Commands < Interface_Minimum_Choked_Commands.Integer)
			{
				Send_Packet = 0;
			}
			else
			{
				if (Choked_Commands < Interface_Maximum_Choked_Commands.Integer)
				{
					if (__builtin_powf(Local_Networked_Origin[0] - Local_Origin[0], 2.f) + __builtin_powf(Local_Networked_Origin[1] - Local_Origin[1], 2.f) + __builtin_powf(Local_Networked_Origin[2] - Local_Origin[2], 2.f) <= 4096.f)
					{
						Send_Packet = 0;
					}
					else
					{
						goto Send_Packet_Label;
					}
				}
				else
				{
					goto Send_Packet_Label;
				}
			}
		}

		__int32 Entity_Number = 1;

		using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Type);

		void* Network_Channel = *(void**)540608912;

		float Latency = Get_Latency_Type(537919008)(Network_Channel, 0);

		float Interpolation_Time = std::clamp(*(float*)607906336, *(float*)542242312, *(float*)542242072) / std::clamp(*(float*)540495208, *(float*)542221264, *(float*)542221408);

		float Corrected_Latency = std::clamp(Latency + Interpolation_Time, 0.f, 1.f);

		float Total_Latency = Get_Latency_Type(537919008)(Network_Channel, 0) + Get_Latency_Type(537919008)(Network_Channel, 1);

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

		struct Target_Structure
		{
			__int32 Priority;

			void* Self;

			__int32 Tick_Number;

			__int8 Valid;

			float Distance;
		};

		static std::vector<Target_Structure> Sorted_Target_List;

		Sorted_Target_List.clear();

		Traverse_Entity_List_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

			if (Player_Data->Priority != -1)
			{
				void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
					{
						if (*(__int32*)((unsigned __int32)Entity + 144) != *(__int32*)((unsigned __int32)Local_Player + 144))
						{
							if (*(__int8*)((unsigned __int32)Entity + 320) == 0)
							{
								float Entity_Time = *(float*)((unsigned __int32)Entity + 104);

								float* Entity_Origin = (float*)((unsigned __int32)Entity + 668);

								Target_Structure Target =
								{
									Player_Data->Priority == -2 ? 0 : Player_Data->Priority,

									Entity,

									(__int32)((Entity_Time + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f),

									__builtin_fabsf(Corrected_Latency - (__int32)(Global_Variables->Tick_Number + (Interface_Alternative.Integer ^ 1) + (Latency - Entity_Time) / Global_Variables->Interval_Per_Tick + 0.5f) * Global_Variables->Interval_Per_Tick) <= 0.2f,

									__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
								};

								Sorted_Target_List.push_back(Target);
							}
						}
					}
				}
			}

			if (Entity_Number != Global_Variables->Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}

		auto Target_List_Sort_Prepare = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			return X.Priority < Y.Priority;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Prepare);

		auto Target_List_Sort_Finish = [](Target_Structure& X, Target_Structure& Y) -> __int8
		{
			if (X.Priority > Y.Priority)
			{
				return 1;
			}

			return X.Distance < Y.Distance;
		};

		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Finish);

		__int8 In_Attack = 0;

		if (Command->Select == 0)
		{
			if (__builtin_fabsf(Global_Variables->Current_Time - Shot_Time) > 0.5f)
			{
				if (Shot_Time == 0)
				{
					Passed_Shot_Time_Check_Label:
					{
						if ((Command->Buttons & 2048) == 0)
						{
							__int8 Send_Packet_Sequence = (Send_Packet == 0) + (Predicted_Send_Packet == 1);

							if (Interface_Alternative.Integer == 1)
							{
								Send_Packet_Sequence = 2;
							}

							if (Interface_Extrapolation.Integer = 1)
							{
								Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];
								void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));
								float* velocity = (float*)((unsigned __int32)Local_Player + 224);
								float currentdirection = deg2rad(atan2(velocity[0], velocity[1]));
								float previousdirection = deg2rad(atan2(velocity[0], velocity[1]));
								float directiondelta = currentdirection - previousdirection;
								float directionvalue = directiondelta / (Global_Variables->Tick_Number - Global_Variables->Tick_Number + Total_Latency);
								__int32 Tick_Number = (*(float*)((unsigned __int32)Entity + 104) + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;
								int simulationticks = __builtin_fabsf(Corrected_Latency - (__int32)(Global_Variables->Tick_Number + Total_Latency / Global_Variables->Interval_Per_Tick + 0.5f - Tick_Number) * Global_Variables->Interval_Per_Tick) <= 0.2f;
								bool lag = ((TIME_TO_TICKS(simulationticks - Corrected_Latency)) > 2);
								float Entity_Origin1 = (float)((unsigned __int32)Entity + 668);

								if (Entity_Origin1 >= 4096.f && lag > 1)
								{
									for (int cmd = 0; cmd < simulationticks; cmd++)
									{

										auto v50 = currentdirection + (directionvalue * Global_Variables->Interval_Per_Tick);
										velocity[0] = cos(deg2rad(v50)) * velocity[0];
										velocity[1] = sin(deg2rad(v50)) * velocity[1];
										Corrected_Latency += Global_Variables->Interval_Per_Tick;
										if (cmd == (simulationticks - 1)) simulationticks = true;
									}
								}
								else if (lag < 2)
								{
									// whatever, do smart lc
								}
							}

							if (Send_Packet_Sequence == 2)
							{
								if (*(float*)((unsigned __int32)Local_Player + 2544) <= Global_Variables->Current_Time)
								{
									using Get_Weapon_Type = void*(__thiscall*)(void* Entity);

									void* Weapon = Get_Weapon_Type(604036352)(Local_Player);

									if (Weapon != nullptr)
									{
										if (*(__int32*)((unsigned __int32)Weapon + 1780) != -1)
										{
											if (*(__int32*)((unsigned __int32)Weapon + 1788) > 0)
											{
												if (*(float*)((unsigned __int32)Weapon + 1720) <= Global_Variables->Current_Time)
												{
													size_t Target_Number = 0;

													using Get_Eye_Position_Type = void(__thiscall*)(void* Entity, float* Eye_Position);

													float Eye_Position[3];

													Get_Eye_Position_Type(604058320)(Local_Player, Eye_Position);

													using Get_Weapon_Information_Type = void*(__thiscall*)(void* Weapon);

													float Weapon_Range = *(float*)((unsigned __int32)Get_Weapon_Information_Type(604037872)(Weapon) + 2020);

													Recent_Player_Data_Number = 0;

													Traverse_Sorted_Target_List_Label:
													{
														if (Target_Number != Sorted_Target_List.size())
														{
															Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

															if (Target->Valid == 1)
															{
																Redirected_Compute_Torso_Rotation((void*)(*(unsigned __int32*)((unsigned __int32)Target->Self + 3968) - 148));

																using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

																float Bones[128][3][4];

																if (Setup_Bones_Type(604209888)((void*)((unsigned __int32)Target->Self + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
																{
																	auto Perform_Trace = [&](float Direction[3]) -> __int8
																	{
																		struct alignas(4) Ray_Structure
																		{
																			__int8 Additional_Bytes[50];
																		};

																		struct Filter_Structure
																		{
																			void* Table;

																			void* Skip;

																			__int8 Additional_Bytes[4];
																		};

																		struct Trace_Structure
																		{
																			__int8 Additional_Bytes_1[68];

																			__int32 Group;

																			__int8 Additional_Bytes_2[4];

																			void* Entity;

																			__int8 Additional_Bytes_3[4];
																		};

																		using Perform_Trace_Type = void(__thiscall*)(void* Tracer, Ray_Structure* Ray, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

																		Ray_Structure Ray;

																		Vector_Normalize(Direction);

																		float End[3]
																		{
																			Eye_Position[0] + Direction[0] * Weapon_Range,

																			Eye_Position[1] + Direction[1] * Weapon_Range,

																			Eye_Position[2] + Direction[2] * Weapon_Range
																		};

																		Initialize_Ray_Type(537380224)(&Ray, Eye_Position, End);

																		Filter_Structure Filter = { (void*)607282692, Local_Player };

																		Trace_Structure Trace;

																		Perform_Trace_Type(537565888)((void*)540446304, &Ray, 1174421515, &Filter, &Trace);

																		using Clip_Trace = void(__cdecl*)(float* Start, float* End, __int32 Mask, Filter_Structure* Filter, Trace_Structure* Trace);

																		End[0] += Direction[0] * 40.f;

																		End[1] += Direction[1] * 40.f;

																		End[2] += Direction[2] * 40.f;

																		Clip_Trace(605426672)(Eye_Position, End, 1174421515, &Filter, &Trace);

																		if (Trace.Entity == Target->Self)
																		{
																			if (Interface_Aim_Intersection.Integer == 0)
																			{
																				return Trace.Group == 1;
																			}

																			return 1;
																		}

																		return 0;
																	};

																	using Get_Studio_Header_Type = void*(__thiscall*)(void* Entity);

																	void* Studio_Header = *(void**)Get_Studio_Header_Type(604188448)(Target->Self);

																	void* Hitbox_Set = (void*)((unsigned __int32)Studio_Header + *(__int32*)((unsigned __int32)Studio_Header + 176));

																	float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox_Set + 836);

																	float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox_Set + 848);

																	float Hitbox_Center[3]
																	{
																		(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2.f,

																		(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2.f,

																		(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2.f
																	};

																	float Hitbox_Z_Vertices[8]
																	{
																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Minimum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Minimum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Minimum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Maximum[2],

																		Bones[14][2][0] * Hitbox_Maximum[0] + Bones[14][2][1] * Hitbox_Maximum[1] + Bones[14][2][2] * Hitbox_Maximum[2]
																	};

																	float* Hitbox_Z_Extremes[2];

																	std::tie(Hitbox_Z_Extremes[0], Hitbox_Z_Extremes[1]) = std::minmax_element(Hitbox_Z_Vertices, &Hitbox_Z_Vertices[sizeof(Hitbox_Z_Vertices) / sizeof(Hitbox_Z_Vertices[0])]);

																	float Target_Origin[3] =
																	{
																		Bones[14][0][0] * Hitbox_Center[0] + Bones[14][0][1] * Hitbox_Center[1] + Bones[14][0][2] * Hitbox_Center[2] + Bones[14][0][3],

																		Bones[14][1][0] * Hitbox_Center[0] + Bones[14][1][1] * Hitbox_Center[1] + Bones[14][1][2] * Hitbox_Center[2] + Bones[14][1][3],

																		Hitbox_Z_Extremes[0][0] + (Hitbox_Z_Extremes[1][0] - Hitbox_Z_Extremes[0][0]) * Interface_Aim_Height.Floating_Point + Bones[14][2][3]
																	};

																	float Direction[3] =
																	{
																		Target_Origin[0] - Eye_Position[0],

																		Target_Origin[1] - Eye_Position[1],

																		Target_Origin[2] - Eye_Position[2]
																	};

																	if (Perform_Trace(Direction) == 1)
																	{
																		Command->Tick_Number = Target->Tick_Number;

																		Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

																		Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

																		Command->Buttons |= 1;

																		if (Interface_Bruteforce.Integer == 1)
																		{
																			__int32 Target_Number = *(__int32*)((unsigned __int32)Target->Self + 80);

																			Player_Data_Structure* Player_Data = &Players_Data[Target_Number];

																			if (Player_Data->Priority != -2)
																			{
																				Recent_Player_Data_Number = Target_Number;

																				Byte_Manager::Copy_Bytes(1, &Previous_Recent_Player_Data, sizeof(Previous_Recent_Player_Data), Player_Data);

																				if (Player_Data->Memory_Tolerance == 0)
																				{
																					if (Player_Data->Tolerance == 0)
																					{
																						Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % Bruteforce_Angles_Count;

																						Player_Data->Tolerance = Interface_Bruteforce_Tolerance.Integer;
																					}
																					else
																					{
																						Player_Data->Tolerance -= 1;
																					}
																				}
																				else
																				{
																					Player_Data->Memory_Tolerance -= 1;
																				}
																			}
																		}

																		goto Found_Target_Label;
																	}
																}
															}

															Target_Number += 1;

															goto Traverse_Sorted_Target_List_Label;

															Found_Target_Label:
															{

															}
														}
													}

													if ((Command->Buttons & 1) == 1)
													{
														float Rotations[2][3][3];

														unsigned __int8 Calculation_Number = 0;

														float Forward[3];

														float Right[3];

														float Up[3];

														Angle_Vectors(Command->Angles, Forward, Right, Up);

														Command->Command_Number = -2076434770;

														Command->Random_Seed = 32;

														using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

														static void* Random_Seed = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11856);

														Random_Seed_Type((unsigned __int32)Random_Seed)((Command->Random_Seed & 255) + 1);

														using Random_Type = float(__cdecl*)(float Minimum, float Maximum);

														static void* Random = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11872);

														float Random_X = Random_Type(Random)(-0.5f, 0.5f) + Random_Type(Random)(-0.5f, 0.5f);

														Weapon_Spread = -1.f;

														using Primary_Attack_Type = void(__thiscall**)(void* Weapon);

														(*Primary_Attack_Type(*(unsigned __int32*)Weapon + 856))(Weapon);

														float Random_Y = Random_Type(Random)(-0.5f, 0.5f) + Random_Type(Random)(-0.5f, 0.5f);

														float Directions[2][3] =
														{
															{
																Forward[0],

																Forward[1],

																Forward[2]
															},

															{
																Forward[0] + Random_X * Weapon_Spread * Right[0] + Random_Y * Weapon_Spread * Up[0],

																Forward[1] + Random_X * Weapon_Spread * Right[1] + Random_Y * Weapon_Spread * Up[1],

																Forward[2] + Random_X * Weapon_Spread * Right[2] + Random_Y * Weapon_Spread * Up[2]
															}
														};

														Weapon_Spread = 0.f;

														Calculate_Rotation_Label:
														{
															Rotations[Calculation_Number][0][0] = Directions[Calculation_Number][0];

															Rotations[Calculation_Number][0][1] = Directions[Calculation_Number][1];

															Rotations[Calculation_Number][0][2] = Directions[Calculation_Number][2];

															Vector_Normalize(Rotations[Calculation_Number][0]);

															Rotations[Calculation_Number][1][0] = Directions[Calculation_Number][1] - Directions[Calculation_Number][2];

															Rotations[Calculation_Number][1][1] = Directions[Calculation_Number][2] - Directions[Calculation_Number][0];

															Rotations[Calculation_Number][1][2] = Directions[Calculation_Number][0] - Directions[Calculation_Number][1];

															Vector_Normalize(Rotations[Calculation_Number][1]);

															Rotations[Calculation_Number][2][0] = Directions[Calculation_Number][1] * Rotations[Calculation_Number][1][2] - Directions[Calculation_Number][2] * Rotations[Calculation_Number][1][1];

															Rotations[Calculation_Number][2][1] = Directions[Calculation_Number][2] * Rotations[Calculation_Number][1][0] - Directions[Calculation_Number][0] * Rotations[Calculation_Number][1][2];

															Rotations[Calculation_Number][2][2] = Directions[Calculation_Number][0] * Rotations[Calculation_Number][1][1] - Directions[Calculation_Number][1] * Rotations[Calculation_Number][1][0];

															Vector_Normalize(Rotations[Calculation_Number][2]);

															if (Calculation_Number != 1)
															{
																Calculation_Number = 1;

																goto Calculate_Rotation_Label;
															}
														}

														float Rotation[3][3] =
														{
															{
																Rotations[0][0][0] * Rotations[1][0][0] + Rotations[0][1][0] * Rotations[1][1][0] + Rotations[0][2][0] * Rotations[1][2][0],

																Rotations[0][0][0] * Rotations[1][0][1] + Rotations[0][1][0] * Rotations[1][1][1] + Rotations[0][2][0] * Rotations[1][2][1],

																Rotations[0][0][0] * Rotations[1][0][2] + Rotations[0][1][0] * Rotations[1][1][2] + Rotations[0][2][0] * Rotations[1][2][2]
															},

															{
																Rotations[0][0][1] * Rotations[1][0][0] + Rotations[0][1][1] * Rotations[1][1][0] + Rotations[0][2][1] * Rotations[1][2][0],

																Rotations[0][0][1] * Rotations[1][0][1] + Rotations[0][1][1] * Rotations[1][1][1] + Rotations[0][2][1] * Rotations[1][2][1],

																Rotations[0][0][1] * Rotations[1][0][2] + Rotations[0][1][1] * Rotations[1][1][2] + Rotations[0][2][1] * Rotations[1][2][2]
															},

															{
																Rotations[0][0][2] * Rotations[1][0][0] + Rotations[0][1][2] * Rotations[1][1][0] + Rotations[0][2][2] * Rotations[1][2][0],

																Rotations[0][0][2] * Rotations[1][0][1] + Rotations[0][1][2] * Rotations[1][1][1] + Rotations[0][2][2] * Rotations[1][2][1],

																Rotations[0][0][2] * Rotations[1][0][2] + Rotations[0][1][2] * Rotations[1][1][2] + Rotations[0][2][2] * Rotations[1][2][2]
															}
														};

														float Rotated_Forward[3] =
														{
															Forward[0] * Rotation[0][0] + Forward[1] * Rotation[0][1] + Forward[2] * Rotation[0][2],

															Forward[0] * Rotation[1][0] + Forward[1] * Rotation[1][1] + Forward[2] * Rotation[1][2],

															Forward[0] * Rotation[2][0] + Forward[1] * Rotation[2][1] + Forward[2] * Rotation[2][2]
														};

														float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

														Command->Angles[0] = 180.f - __builtin_atan2f(-Rotated_Forward[2], __builtin_hypotf(Rotated_Forward[0], Rotated_Forward[1])) * 180.f / 3.1415927f - Recoil[0] * 2.f;

														Command->Angles[1] = 180.f + __builtin_atan2f(Rotated_Forward[1], Rotated_Forward[0]) * 180.f / 3.1415927f - Recoil[1] * 2.f;

														float Rotated_Up[3] =
														{
															Up[0] * Rotation[0][0] + Up[1] * Rotation[0][1] + Up[2] * Rotation[0][2],

															Up[0] * Rotation[1][0] + Up[1] * Rotation[1][1] + Up[2] * Rotation[1][2],

															Up[0] * Rotation[2][0] + Up[1] * Rotation[2][1] + Up[2] * Rotation[2][2]
														};

														Command->Angles[2] = 180.f + __builtin_atan2f(Rotated_Forward[1] * Rotated_Up[0] - Rotated_Forward[0] * Rotated_Up[1], Rotated_Forward[0] * (Rotated_Forward[0] * Rotated_Up[2] - Rotated_Forward[2] * Rotated_Up[0]) - Rotated_Forward[1] * (Rotated_Forward[2] * Rotated_Up[1] - Rotated_Forward[1] * Rotated_Up[2])) * 180.f / 3.1415927f - Recoil[2] * 2.f;

														In_Attack = 1;

														Send_Packet = Interface_Alternative.Integer * 2;

														Shot_Time = Global_Variables->Current_Time;
													}
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
					Shot_Time = 0;

					if (Recent_Player_Data_Number == 0)
					{
						goto Passed_Shot_Time_Check_Label;
					}

					Byte_Manager::Copy_Bytes(1, &Players_Data[Recent_Player_Data_Number], sizeof(Previous_Recent_Player_Data), &Previous_Recent_Player_Data);

					goto Passed_Shot_Time_Check_Label;
				}
			}
		}

		Command->Buttons &= ~2048;

		if (In_Attack == 0)
		{
			Command->Buttons &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				Command->Angles[0] = Interface_Angle_X.Floating_Point;

				float* Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Self + 668);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Origin[0],

					Target_Origin[1] - Local_Origin[1]
				};

				if (Send_Packet == 0) {

					if (Interface_At_Targets.Floating_Point == 1) {
						if ((Command->Command_Number % 2) == 0) {
							Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_First_Choked_Angle_Y.Floating_Point;
						}
						else {
							Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Second_Choked_Angle_Y.Floating_Point;
						}
					}
					else {
						if ((Command->Command_Number % 2) == 0) {
							Command->Angles[1] += Interface_First_Choked_Angle_Y.Floating_Point;
						}
						else {
							Command->Angles[1] += Interface_Second_Choked_Angle_Y.Floating_Point;
						}
					}
				}
				else {
					if (Interface_At_Targets.Floating_Point == 1) {
						Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180 / 3.1415927f + Interface_Angle_Y.Floating_Point + jitter(0.0, Interface_Jitter_Range.Floating_Point);
					}
					else {
						Command->Angles[1] += Interface_Angle_Y.Floating_Point + jitter(0.0, Interface_Jitter_Range.Floating_Point);
					}
				}
			}
			else
			{
				if (Interface_Enemy_Check.Integer == 0) //"remains accessible via console commands"
				{
					if (Send_Packet == 0)
					{
						Command->Angles[0] = Interface_Angle_X.Floating_Point;

						if ((Command->Command_Number % 2) == 0)
						{
							Command->Angles[1] += Interface_First_Choked_Angle_Y.Floating_Point;
						}
						else
						{
							Command->Angles[1] += Interface_Second_Choked_Angle_Y.Floating_Point;
						}
					}
					else
					{
						Command->Angles[1] += Interface_Angle_Y.Floating_Point;
					}
				}
			}
		}

		auto Compress_Angle = [](float Value, __int32 Shift) -> float
		{
			return ((__int32)(Value / 360.f * Shift) & Shift - 1) * (360.f / Shift);
		};

		Command->Angles[0] = Compress_Angle(Command->Angles[0], 65536);

		Command->Angles[1] = Compress_Angle(Command->Angles[1], 65536);

		Command->Angles[2] = Compress_Angle(Command->Angles[2], 256);

		Correct_Movement();

		if (Send_Packet == 0)
		{
			__int32 Sequence_Number = *(__int32*)((unsigned __int32)Network_Channel + 8) = Redirected_Send_Datagram(Network_Channel, nullptr);

			Sequences[Sequence_Number % 90] = *(__int32*)540627868;
		}
		else
		{
			Byte_Manager::Copy_Bytes(1, Update_Animation_Angles, sizeof(Update_Animation_Angles), Command->Angles);
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 24) = Send_Packet;
	}

	(decltype(&Redirected_Copy_Command)(Original_Copy_Command_Caller))(Unknown_Parameter, Command);
}