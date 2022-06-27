#include <Windows.h>
#include <string>
#include <filesystem>

#include "ScriptEngine.h"
#include "ScriptRegistrator.h"
#include "Console.hpp"

#include "InfinityPlugin.h"

namespace fs = std::filesystem;

void Infinity::LoadPlugins()
{
	// load all plugins and call "OnPluginLoad"
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

void Infinity::RegisterScriptClass(BaseScriptClass* pScriptClass)
{
	// add script class to registrator table
	BaseScriptRegistrator* g_RegistratorClass = new BaseScriptRegistrator(pScriptClass);
	(*g_pGlobalRegistrator)->GetLast()->Insert(g_RegistratorClass);
}
Infinity::BaseScriptClass::BaseScriptClass(const char* name)
{
	this->className = name;
}
const char* Infinity::BaseScriptClass::GetName() 
{
	return this->className;
}
void Infinity::BaseScriptClass::RegisterFunctions(RegistrationFunction registerMethod)
{
	return; // not implemnented
}


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