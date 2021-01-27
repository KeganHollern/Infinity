#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;


//	class ExamplePluginObject {
//		void ExamplePluginObject() { Print("Constructed ExamplePluginObject!"); }
//		void ~ExamplePluginObject() { Print("Deconstructed ExamplePluginObject!"); }
//		proto native static void TestStaticFunction();
//		proto native void NonStaticFunction();
//  }
void TestStaticFunction()
{
	Infinity::Logging::Print("Call to static class function!");
}
void NonStaticFunction(Framework::ManagedScriptInstance* pInstance)
{
	if (pInstance)
	{
		Framework::type* pType = pInstance->pType;
		if (pType)
		{
			Infinity::Logging::Print("Call to non-static function from type: %s", pType->name);
			return;
		}
	}
	Infinity::Logging::Print("Call to non-static function had invalid argument pInstance");
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void ClassProtosPluginInit()
{
	void* pObject = Infinity::Enfusion::Enscript::RegisterObject("ExamplePluginObject");

	if (pObject)
	{
		Infinity::Enfusion::Enscript::RegisterFunctionForObject(pObject, "TestStaticFunction", &TestStaticFunction, false);
		Infinity::Enfusion::Enscript::RegisterFunctionForObject(pObject, "NonStaticFunction", &NonStaticFunction, false);
	}

	Infinity::Logging::Print("ClassProtos Plugin Loaded.");
}