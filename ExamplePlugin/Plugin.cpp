#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "../BIDebugEngine/Plugins.h"


struct testclass {
	char* name;
};

//this is wrong
void* CreateTestClass(char* name)
{
	Infinity::Logging::Print("Creating New Test Class! w/ Name: %s", name);

	testclass* result = (testclass*)malloc(sizeof(testclass));
	if(result)
		result->name = name;
	
	return result;
}
//this doesn't work because the above is wrong (can't test it until above is correct)
char* GetTestClassName(void* arg1)
{
	Infinity::Logging::Print("Getting Test Class Name!");

	if (!arg1)
		return NULL;

	return ((testclass*)arg1)->name;
}
//this works :)
int GetInternalValue(char* string_input)
{
	Infinity::Logging::Print("Getting String Length of '%s'", string_input);
	return strlen(string_input);
}
void TestPluginFunction()
{
	Infinity::Logging::Print("Test!");
}
//we need to export this function
void __declspec(dllexport) OnPluginLoad()
{
	Infinity::Logging::Print("Plugin Load!"); //plugins can write to console/logfile by using Print & Error methods

	Infinity::Enfusion::Enscript::RegisterFunction("TestPluginFunc", &TestPluginFunction); //this function will be imported from BIDebugEngine.dll

	Infinity::Enfusion::PrintToConsole("Plugin Console Print Test!");


	void* pCustomType = Infinity::Enfusion::Enscript::RegisterObject("ExampleTestClass");
	if (pCustomType)
	{
		Infinity::Enfusion::Enscript::RegisterFunctionForObject(pCustomType, "Create", &CreateTestClass, false);
		Infinity::Enfusion::Enscript::RegisterFunctionForObject(pCustomType, "GetName", &GetTestClassName, false);
		Infinity::Enfusion::Enscript::RegisterFunctionForObject(pCustomType, "GetInternalValue", &GetInternalValue, false);
	}
	else
	{
		Infinity::Logging::Print("Failed to register 'ExampleTestClass'. Are you sure the enscript class is defined properly?");
	}

	Infinity::Logging::Print("All Functions Registered!");
}