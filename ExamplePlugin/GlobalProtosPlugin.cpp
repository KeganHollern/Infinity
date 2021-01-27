#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"


//proto native void WriteToConsole(string message);
void WriteToConsole(char* message)
{
	Infinity::Logging::Print("ExamplePlugin: %s", message);
	Infinity::Enfusion::PrintToConsole("ExamplePlugin: %s", message);
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void GlobalProtosPluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("WriteToConsole", &WriteToConsole);
	Infinity::Logging::Print("GlobalProtos Plugin Loaded.");
}