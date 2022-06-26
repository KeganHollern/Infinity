#include <string>
#include <MinHook.h>
#include <Windows.h>
#include <stdint.h>

#include "console.hpp"
#include "infinity.h"
#include "plugins.h"

#include "reforger.h"

const std::string ENSCRIPT_REGISTER_FUNCTION_GLOBAL = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8B F9 48 8B D9";
const std::string ENSCRIPT_INIT_FUNCTIONS = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 30 4C 8B F2";

uint64_t* Infinity::HK_Reforger_InitModules(void* pScriptContext, void* pUnknown) {
	Debugln("initmodules called");

	Reforger* pReforger = (Reforger*)g_pEngine;
	if (!pReforger)
	{
		Errorln("g_pEngine is null!");
		return NULL;
	}
	if (!pReforger->oInitModules)
	{
		Errorln("oInitModules is null!");
		return NULL;
	}
	uint64_t* result = pReforger->oInitModules(pScriptContext, pUnknown);

	// load plugins
	Infinity::LoadPlugins(pScriptContext);

	return result;
}
const char* Infinity::Reforger::Game() { return "Reforger"; };
void Infinity::Reforger::Init()
{
	Debugln("arma reforger init started.");

	// find all our functions
	fRegisterGlobal = (ADDFUNCTION)this->FindFunction("Enscript::RegisterGlobalFunction", ENSCRIPT_REGISTER_FUNCTION_GLOBAL, 0);
	if (!fRegisterGlobal) return;

	void* pInitFunctions = this->FindFunction("Enscript::InitModules", ENSCRIPT_INIT_FUNCTIONS, 0);
	if (!pInitFunctions) return;

	// hook all the functions we need to
	MH_STATUS status = MH_Initialize();
	if (status != MH_ERROR_ALREADY_INITIALIZED && status != MH_OK)
	{
		Errorln("Failed to initialize minhook.");
		return;
	}

	status = (MH_STATUS)this->ApplyHook(pInitFunctions, &HK_Reforger_InitModules, reinterpret_cast<LPVOID*>(&this->oInitModules));
	if (status != MH_OK)
	{
		Errorln("Failed to apply initmodules hook.");
		return;
	}

	Debugln("arma reforger init completed");
}

void* Infinity::Reforger::RegisterGlobal(void* pScriptContext, const char* name, void* function)
{
	if (!fRegisterGlobal)
	{
		Errorln("Could not register '%s'. Registeration function not found.", name);
		return nullptr;
	}
	if (!function)
	{
		Errorln("Could not register '%s'. Native function pointer is NULL.", name);
		return nullptr;
	}

	return fRegisterGlobal(pScriptContext, name, function, 0);
}

bool Infinity::Reforger::RunFunction(void* object, const char* function, long long arg4)
{
	if (!object)
	{
		Errorln("Could not run '%s'. Object pointer is NULL.", function);
		return false;
	}
	if (!fRunFunction)
	{
		Errorln("Could not run '%s'. Native function pointer is NULL.", function);
		return false;
	}

	int64_t result = 0;;
	int64_t* pResult = this->fRunFunction(object, &result, (char*)function, arg4);
	Debugln("Function run result: %p", pResult);
	return true;
}