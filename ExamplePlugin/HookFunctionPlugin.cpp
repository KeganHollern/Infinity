#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

typedef uint64_t(__fastcall* script_FileExist)(int64_t* FunctionCtx, int64_t* pResult);

script_FileExist dayzFileExist;

uint64_t script_FileExist_hooked(int64_t* FunctionCtx, int64_t* pResult)
{
	Infinity::Logging::Print("Call to FileExist!");
	if (!dayzFileExist)
	{
		Infinity::Logging::Error("Failed to call base FileExist function. NULL!");
		return NULL;
	}
	return dayzFileExist(FunctionCtx, pResult);
}



/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void HookFunctionPluginInit()
{
	void* pFunction = Infinity::Utils::FindPattern("48 89 5C 24 ? 57 48 83 EC ? 48 8B 01 48 8B F9 48 8B DA");
	if (pFunction)
	{
		HRESULT hr = Infinity::Utils::HookFunction(pFunction, &script_FileExist_hooked, reinterpret_cast<LPVOID*>(&dayzFileExist));
		if (hr == S_OK)
		{
			Infinity::Logging::Print("Hooked FileExist");
		}
		else
			Infinity::Logging::Error("Failed to hook FileExist");
	}
	else
		Infinity::Logging::Error("Failed to find FileExist");
	
	Infinity::Logging::Print("HookFunction Plugin Loaded.");
}