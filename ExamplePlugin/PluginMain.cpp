#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

void __declspec(dllexport) OnPluginLoad()
{
	Infinity::Logging::Print("[ExamplePlugin] Loading Internal Plugins!");


	GlobalProtosPluginInit();
	ClassProtosPluginInit();
	FindPatternPluginInit();
	CallbacksPluginInit();
	HookFunctionPluginInit();
	SetValuePluginInit();


	Infinity::Logging::Print("[ExamplePlugin] All Plugins Loaded!");

}