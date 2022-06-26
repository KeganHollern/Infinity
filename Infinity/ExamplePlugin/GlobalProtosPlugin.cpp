#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"


//proto native void WriteToConsole(string message);
void WriteToConsole(char* message)
{
	Infinity::Logging::Println("ExamplePlugin: %s", message);
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void GlobalProtosPluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("WriteToConsole", &WriteToConsole);
	Infinity::Logging::Println("GlobalProtos Plugin Loaded.");
}