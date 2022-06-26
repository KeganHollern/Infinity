#include <plugins.h>

#include "ExamplePlugin.h"

using namespace Infinity::Logging;

void __declspec(dllexport) OnPluginLoad()
{
	GlobalProtosPluginInit();
	ClassProtosPluginInit();
	FindPatternPluginInit();
	CallbacksPluginInit();
	HookFunctionPluginInit();
	SetValuePluginInit();
	ArrayUsagePluginInit();

	Println("Example plugin loaded!");

}