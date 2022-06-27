#include <InfinityPlugin.h>

#include "ExampleClass.h"

using namespace Infinity;
using namespace Infinity::Logging;

// this routine is called when it's time to register our script classes
__declspec(dllexport) void OnPluginLoad()
{
	Println("Loading example plugin.");

	RegisterScriptClass(new ExampleClass()); // register our example class

	Println("Example plugin loaded.");
}