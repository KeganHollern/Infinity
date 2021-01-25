#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "../BIDebugEngine/Plugins.h"
#include "../BIDebugEngine/PluginTypes.h"

namespace fs = std::filesystem;
namespace Framework = Infinity::Enfusion::Enscript::Framework;
namespace Enscript = Infinity::Enfusion::Enscript;
namespace Enfusion = Infinity::Enfusion;
namespace Logging = Infinity::Logging;
namespace Utils = Infinity::Utils;


//proto native void NativeTypeTest(typename type) <--- in dayz
void NativeTypeTest(Framework::type* pType)
{
	if (!pType)
		return;
	

	Logging::Print("NativeTypeTest(%p)", pType);
	Logging::Print("Type Name: %s", pType->name);
}
//proto void NonNativeTypeTest(typename type)
void NonNativeTypeTest(Enscript::FunctionContext* pContext, void* pUnkn)
{
	if (!pContext)
		return;
	if (!pContext->GetArgument(0))
		return;

	Framework::type* pType = (Framework::type*)pContext->GetArgument(0)->Value;


	Logging::Print("NonNativeTypeTest(%p)", pType);
	Logging::Print("Type Name: %s", pType->name);
}

//proto void SetOutputValueTest(typename type, out string name);
void SetOutputValueTest(Enscript::FunctionContext* pContext, void* pUnkn)
{
	if (!pContext)
		return;
	if (!pContext->GetArgument(0))
		return;
	if (!pContext->GetArgument(1))
		return;

	Framework::type* pType = (Framework::type*)pContext->GetArgument(0)->Value;
	pContext->GetArgument(1)->Value = pType->name;
}
//proto native void WriteToConsole(string value);
void WriteToConsole(char* value)
{
	Logging::Print(value);
	Enfusion::PrintToConsole(value);
}

//proto void RunCallbackTest(Class anyvalue);
void RunCallbackTest(Enscript::FunctionContext* pContext, void* pUnkn)
{
	if (!pContext || !pContext->GetArgument(0))
		return;

	Framework::ManagedScriptInstance* pDummyClass = (Framework::ManagedScriptInstance*)pContext->GetArgument(0)->Value;
	Logging::Print("Dummy Class: %p", pDummyClass);
	if (pDummyClass)
	{
		Framework::type* type = pDummyClass->pType;
		Logging::Print("Dummy Class Type: %p", type);
		if (type)
		{
			Logging::Print("Dummy Class Typename: %s", type->name);
			
			//void Callback() {}
			Enscript::RunFunction(pDummyClass, "Callback", NULL);
		}
	}
}


//proto static native ScriptModule LoadScript(ScriptModule parent, string filepath);
typedef void*** (__fastcall* script_LoadScript)(void* pParentModule, char* filePath);
script_LoadScript dayzLoadScript;

//proto native ScriptModule LoadSpecialModule(ScriptModule parent);
void*** load_special_module(Framework::ScriptModule* pModule)
{
	if (!dayzLoadScript)
	{
		Logging::Error("Failed to find dayz load script function");
		return NULL;
	}

	char buffer[MAX_PATH];
	strcpy(buffer, "C:\\Users\\kegan\\Documents\\Test\\");
	//Enfusion::GetProfilePath(buffer); //D:\SteamLibrary\steamapps\common\DayZServer\profiles\

	std::string path(buffer);

	if (!fs::exists(path))
	{
		Logging::Error("Failed to find profile path!");
		return NULL;
	}
	path += "test.c";

	//write special sauce to disk
	std::ofstream of(path, std::ios::trunc);
	of << \
		"void test_func() { \
		WriteToConsole(\"TESTING SPECIAL MODULE FROM $dab!\"); \
		FileHandle file_handle = OpenFile(\"$dab:dab_message.txt\", FileMode.READ); \
		string line_content; \
		while ( FGets( file_handle,  line_content ) > 0 ) { \
			 WriteToConsole(line_content); \
		} \
		CloseFile(file_handle); \
		WriteToConsole(\"DONE READ!\"); \
		file_handle = OpenFile(\"$dab:dab_message.txt\", FileMode.APPEND); \
		if(file_handle) { \
			FPrintln(file_handle,\"New Line!\"); \
			CloseFile(file_handle); \
			WriteToConsole(\"WRITE SUCCESS!\");  \
		} else { \
			WriteToConsole(\"FAILED TO OPEN FOR WRITE!\"); \
		} \
	}";
	of.close();

	Logging::Print("Loading Special Module!");

	return dayzLoadScript(pModule, (char*)"$dab:test.c");
}


//we need to export this function
void __declspec(dllexport) OnPluginLoad()
{
	dayzLoadScript = (script_LoadScript)Utils::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 4C 8B C1");


	Logging::Print("Loading Test Plugin..."); //plugins can write to console/logfile by using Print & Error methods
	

	Enscript::RegisterFunction("NativeTypeTest", &NativeTypeTest);
	Enscript::RegisterFunction("NonNativeTypeTest", &NonNativeTypeTest);
	Enscript::RegisterFunction("SetOutputValueTest", &SetOutputValueTest);
	Enscript::RegisterFunction("WriteToConsole", &WriteToConsole);
	Enscript::RegisterFunction("RunCallbackTest", &RunCallbackTest);

	Enscript::RegisterFunction("LoadSpecialModule", &load_special_module);

	if (Enfusion::RegisterKeyPath("C:\\Users\\kegan\\Documents\\Test", "dab", true))//should allow read & write from "$dab:<file_name>"
		Logging::Print("Registered Key Path!");
	else
		Logging::Error("Failed to register key path!");

	Enfusion::PrintToConsole("Loaded Test");
}

