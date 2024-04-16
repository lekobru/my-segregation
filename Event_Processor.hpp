#include <iostream>
#include <cstdlib> 
#include <cstdio>  


__int32 Recent_Player_Data_Number;
float Shot_Time;
static int round_counter = 0;



void __stdcall Event_Processor(void* Event)
{
    void* Local_Player = *(void**)607867332;

    if (Local_Player != nullptr)
    {
        using Get_Name_Type = char* (__thiscall*)(void* Event);
        char* Name = Get_Name_Type(537579280)(Event);

        using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);
        using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

        __int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);





        if (Name[0] == 'p')
        {
            __int32 Victim_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));
            __int32 Killer_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"attacker", nullptr));

            if (Victim_Number != Killer_Number)
            {
                if (Killer_Number != 0)
                {
                    if (Killer_Number == Local_Player_Number)
                    {
                        if (Name[7] == 'd')
                        {
                            if (Interface_Commentator.Integer == 1)
                            {
                                PlaySoundW((wchar_t*)CoD, nullptr, SND_ASYNC | SND_MEMORY);
                            }
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            Shot_Time *= Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr)) != Local_Player_Number;
        }
    }
}
