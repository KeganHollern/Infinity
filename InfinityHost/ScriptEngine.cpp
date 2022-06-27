#include <Windows.h>
#include <stdio.h>
#include <string>

#include "Patterns.h"
#include "Console.hpp"

#include "ScriptEngine.h"

const std::string PATTERN_SCRIPT_TABLE_HEAD = "48 8B 1D ? ? ? ? 48 8B F2 4C 8B F1";
const std::string PATTERN_REGISTER_CLASS = "48 83 EC 38 4C 8B C2 41 B1 02";
const std::string PATTERN_REGISTER_CLASS_FUNCTION = "48 89 5C 24 ? 57 48 83 EC 30 0F B6 44 24 ? 48 8B D9"; 


Enscript__RegisterClass fRegisterClass = NULL;
Enscript__RegisterClassStaticFunction fRegisterClassStaticFunction = NULL;
ScriptRegistrator** g_pGlobalRegistrator = NULL;
const char** g_pStringModuleGame = NULL;


bool InitScriptEngine()
{
	Debugln("Init script engine.");
	// find this static address by it's usage during ModuleGame registration
	void* address = FindPattern(PATTERN_SCRIPT_TABLE_HEAD, GetModuleHandle(NULL), 3);
	uint32_t rel = *(uint32_t*)address;
	uint64_t global_registrator = (uint64_t)address + 4 + rel;

	g_pGlobalRegistrator = (ScriptRegistrator**)global_registrator;

	fRegisterClass = (Enscript__RegisterClass)FindPattern(PATTERN_REGISTER_CLASS, GetModuleHandle(NULL), 0);
	fRegisterClassStaticFunction = (Enscript__RegisterClassStaticFunction)FindPattern(PATTERN_REGISTER_CLASS_FUNCTION, GetModuleHandle(NULL), 0);

	Debugln("Done. %p, %p, %p.", g_pGlobalRegistrator, fRegisterClass, fRegisterClassStaticFunction);

	return true;
}