
#include <Windows.h>
#include <stdio.h>
#include <MinHook.h>
#include <filesystem>

#include "console.hpp"
#include "patterns.h"
#include "infinity.h"

#include "plugins.h"

namespace fs = std::filesystem;


void* g_pScriptContext;


#pragma region Logging
void Infinity::Logging::Println(const char* format, ...)
{
	printf("PLUGIN       : ");
	va_list vl;
	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);
	printf("\n");
}
void Infinity::Logging::Debugln(const char* format, ...)
{
	printf("PLUGIN    (D): ");
	va_list vl;
	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);
	printf("\n");
}
void Infinity::Logging::Warnln(const char* format, ...)
{
	printf("PLUGIN    (W): ");
	va_list vl;
	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);
	printf("\n");
}
void Infinity::Logging::Errorln(const char* format, ...)
{
	printf("PLUGIN    (E): ");
	va_list vl;
	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);
	printf("\n");
}
#pragma endregion

#pragma region Utils
void* Infinity::Utils::FindPattern(const char* binary_ninja_pattern)
{
	Debugln("Finding pattern '%s' in enfusion.", binary_ninja_pattern); // uses INFINITY: prefix
	return Infinity::FindPattern(binary_ninja_pattern, GetModuleHandle(NULL), 0);
}
HRESULT Infinity::Utils::HookFunction(void* pAddress, void* pHookFunction, void** pOriginal) {
	MH_STATUS status = (MH_STATUS)g_pEngine->ApplyHook(pAddress, pHookFunction, pOriginal);
	if (status == MH_OK)
		return S_OK;
	return E_FAIL;
}
#pragma endregion

#pragma region Enfusion
const char* Infinity::Enfusion::GetGame()
{
	return g_pEngine->Game();
}
/*
bool Infinity::Enfusion::RegisterKeyPath(const char* directory, const char* key, bool allow_write = true)
{
	return false;
}
void* Infinity::Enfusion::MemAlloc(SIZE_T size)
{
	return nullptr;
}
*/
#pragma endregion

#pragma region Enscript
void* Infinity::Enfusion::Enscript::RegisterFunction(const char* name, void* function)
{
	void* result = g_pEngine->RegisterGlobal(g_pScriptContext, name, function);
	Debugln("Registered '%s'. Result: '%p'.", name, result);
	if (!result)
	{
		Warnln("Failed to register '%s'. Enscript not defined?", name);
	}
	return result;
}

bool Infinity::Enfusion::Enscript::RunFunction(void* object, const char* function, long long arg4)
{
	return g_pEngine->RunFunction(object, function, arg4);
}
#pragma endregion

#pragma region Plugins

void Infinity::LoadPlugins(void* pScriptContext)
{
	g_pScriptContext = pScriptContext;

	Println("Loading infinity plugins.");

	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string directory = std::string(buffer).substr(0, pos) + "\\Plugins\\";

	if (!fs::exists(directory))
	{
		Warnln("Plugin directory does not exist. Expected at '%s'.", directory.c_str());
		return;
	}

	Debugln("Loading plugins from '%s'.", directory.c_str());
	std::string ext(".dll");
	for (auto& p : fs::recursive_directory_iterator(directory))
	{
		if (p.path().extension() == ext)
		{
			Debugln("Found plugin '%s'.", p.path().stem().string().c_str());
			HMODULE hLib = LoadLibraryW(p.path().c_str());
			if (hLib)
			{
				ONPLUGINLOAD OnPluginLoad = (ONPLUGINLOAD)GetProcAddress(hLib, "?OnPluginLoad@@YAXXZ");
				if (OnPluginLoad)
					OnPluginLoad();
			}

		}
	}
}
#pragma endregion