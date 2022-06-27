
#include <Windows.h>
#include <stdio.h>
#include <filesystem>

#include "console.hpp"
#include "patterns.h"
#include "infinity.h"

#include "plugins.h"

namespace fs = std::filesystem;




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
#pragma endregion



#pragma region Plugins

void Infinity::LoadPlugins(void* pScriptContext)
{

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