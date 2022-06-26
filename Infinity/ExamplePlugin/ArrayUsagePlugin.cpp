#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>
#include <combaseapi.h>
#include <string>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;
namespace Enscript = Infinity::Enfusion::Enscript;

//proto native void PrintStringsFromArray(notnull array<string> arr);
void PrintStringsFromArray(Framework::Array* pArray)
{
	if (!pArray)
	{
		Infinity::Logging::Errorln("Array NULL!");
		return;
	}
	for (int i = 0; i < pArray->Size; i++)
	{
		char* value = pArray->GetValue<char*>(i);
		if (value && strlen(value) > 0)
		{
			Infinity::Logging::Println("%s", value);
		}
	}

}
//proto native void PrintClassNames(notnull array<Class> arr);
void PrintClassNames(Framework::Array* pArray)
{
	if (!pArray)
	{
		Infinity::Logging::Errorln ("Array NULL!");
		return;
	}
	for (int i = 0; i < pArray->Size; i++)
	{
		Framework::ManagedScriptInstance* value = pArray->GetValue<Framework::ManagedScriptInstance*>(i);
		if (value)
			if (value->pType && value->pType->name)
				Infinity::Logging::Println ("Entry: %p | %s", value, value->pType->name);
	}
}
//proto native void PrintMapInfo(notnull map<string, Class> arr);
void PrintMapInfo(Framework::Hashmap* pMap)
{
	if (!pMap)
	{
		Infinity::Logging::Errorln("Map NULL!");
		return;
	}
	Infinity::Logging::Println("Map: %p", pMap);
	for (int i = 0; i < pMap->Size; i++)
	{
		char* key = pMap->GetKey<char*>(i);
		Framework::ManagedScriptInstance* value = pMap->ElementAt<Framework::ManagedScriptInstance*>(i);
		if (key && value && value->pType && value->pType->name)
		{
			Framework::ManagedScriptInstance* test = pMap->Get<char*, Framework::ManagedScriptInstance*>(key);
			if(test == value)
				Infinity::Logging::Println("Map: %s, %s (successfully called Get)", key, value->pType->name);
			else
				Infinity::Logging::Println("Map: %s, %s (failed to call Get)", key, value->pType->name);
		}
	}
}


void ArrayUsagePluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("PrintClassNames", &PrintClassNames);
	Infinity::Enfusion::Enscript::RegisterFunction("PrintMapInfo", &PrintMapInfo);
	Infinity::Enfusion::Enscript::RegisterFunction("PrintStringsFromArray", &PrintStringsFromArray);
	Infinity::Logging::Println("ArrayUsage Plugin Loaded.");
}