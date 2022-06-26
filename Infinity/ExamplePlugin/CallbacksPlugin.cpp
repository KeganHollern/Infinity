#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;

//
//	class CallbackTest {
//		void Callback() { Print("Running Callback On New Thread!"); }
//	}
//	proto native void RunCallbackTest(CallbackTest test);
//
//	void TEST_CALLBACKS() {
//		CallbackTest test = new CallbackTest;
//		RunCallbackTest(test);
//	}
//
void RunCallbackTest(Framework::ManagedScriptInstance* pCallbackTest)
{
	if(Infinity::Enfusion::Enscript::RunFunction(pCallbackTest, "Callback", NULL))
		Infinity::Logging::Println("Ran callback!");
	else
		Infinity::Logging::Errorln("Error running callback!");
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void CallbacksPluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("RunCallbackTest", &RunCallbackTest);

	Infinity::Logging::Println("Callbacks Plugin Loaded.");
}