// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <string>
#include <vector>
#include <stdint.h>

#include "types.h"
#include "Utils.h"
#include "Console.h"
#include "Engine.h"

void Start()
{
    if (Utils::IsDebug())
        Console::Create();
    else
        Console::ToFile();

    DayZ::Engine::HookInit();
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Start();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

