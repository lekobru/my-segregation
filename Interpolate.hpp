void* Original_Interpolate_Caller;

__int8 __thiscall Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
    if (Entity != *(void**)607867332)
    {
        if (*(void**)Entity == (void*)607350148)
        {
            return 1;//or 0
        }
    }

    return (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller))(Entity, Unknown_Parameter);
}