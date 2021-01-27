#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <filesystem>
#include <fstream>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;
namespace Logging = Infinity::Logging;
namespace fs = std::filesystem;

typedef void*** (__fastcall* script_LoadScript)(void* pParentModule, char* filePath);
script_LoadScript dayzLoadScript;



//proto native void PrintToDayZConsole(string value);
//proto native ScriptModule LoadSpecialModule(ScriptModule parent);
void PrintToDayZConsole(char* value)
{
	Logging::Print(value);
	Infinity::Enfusion::PrintToConsole(value);
}

void*** LoadSpecialModule(Framework::ScriptModule* pModule)
{
	if (!dayzLoadScript)
	{
		Logging::Error("Failed to find dayz load script function");
		return NULL;
	}

	//get file paths on disk
	fs::path path = fs::temp_directory_path();
	fs::path code_file = path / "test.c";
	fs::path message_file = path / "test_msg.txt";


	//write message to disk
	std::ofstream msgof(message_file, std::ios::trunc);
	msgof << "This is a test message" << std::endl;
	msgof.close();

	//write code file to disk
	std::ofstream codeof(code_file, std::ios::trunc);
	codeof << \
		"void test_func() { \
			PrintToDayZConsole(\"TESTING SPECIAL MODULE FROM $temp!\"); \
			FileHandle file_handle = OpenFile(\"$temp:test_msg.txt\", FileMode.READ); \
			string line_content; \
			while ( FGets( file_handle,  line_content ) > 0 ) { \
				 PrintToDayZConsole(line_content); \
			} \
			CloseFile(file_handle); \
			PrintToDayZConsole(\"DONE READ!\"); \
			file_handle = OpenFile(\"$temp:test_msg.txt\", FileMode.APPEND); \
			if(file_handle) { \
				FPrintln(file_handle,\"New Line!\"); \
				CloseFile(file_handle); \
				PrintToDayZConsole(\"WRITE SUCCESS!\");  \
			} else { \
				PrintToDayZConsole(\"FAILED TO OPEN FOR WRITE!\"); \
			} \
		}";
	codeof.close();

	Logging::Print("Loading Special Module!");

	return dayzLoadScript(pModule, (char*)"$temp:test.c"); //call the LoadScript function from ScriptModule class in enscript
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void FindPatternPluginInit()
{
	dayzLoadScript = (script_LoadScript)Infinity::Utils::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 4C 8B C1");

	Infinity::Enfusion::Enscript::RegisterFunction("LoadSpecialModule", &LoadSpecialModule); 
	Infinity::Enfusion::Enscript::RegisterFunction("PrintToDayZConsole", &PrintToDayZConsole);

	//register temp directory as $temp in engine
	if (Infinity::Enfusion::RegisterKeyPath(fs::temp_directory_path().string().c_str(), "temp", true))//should allow read & write from "$dab:<file_name>"
		Logging::Print("Registered Key Path!");
	else
		Logging::Error("Failed to register key path!");

	Infinity::Logging::Print("FindPattern Plugin Loaded.");
}