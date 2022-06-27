
#include <string>
#include <stdint.h>
#include <functional>

#include "ScriptEngine.h"
#include "InfinityPlugin.h"
#include "Console.hpp"

#include "ScriptRegistrator.h"


ScriptRegistrator::ScriptRegistrator() 
{
	pModuleName = *g_pStringModuleGame;
	pNext = NULL;
	pClass = NULL;
}
ScriptRegistrator::~ScriptRegistrator() {
	Errorln("Uh oh! Unsafe deconstruct!");
}
ScriptRegistrator* ScriptRegistrator::GetLast() 
{
	ScriptRegistrator* result = this;
	do
	{
		if (!result->pNext) break;
		result = result->pNext;
	} while (true);
	return result;
}
void ScriptRegistrator::Insert(ScriptRegistrator* registrator)
{
	ScriptRegistrator* old_next = this->pNext; // expect NULL
	this->pNext = registrator;
	registrator->pNext = old_next; // expect NULL
}
ScriptRegistrator* ScriptRegistrator::GetNext()
{
	return this->pNext;
}
const char* ScriptRegistrator::GetName()
{
	if (!this->pModuleName) return "";
	return this->pModuleName;
}
bool ScriptRegistrator::HasChild(ScriptRegistrator* child)
{
	if (!child) return false;

	ScriptRegistrator* test = this;
	do
	{
		if (test == child) return true;
		test = test->pNext;
	} while (test);
	return false;
}


// -------------------------------------------------------------

BaseScriptRegistrator::BaseScriptRegistrator(Infinity::BaseScriptClass* pParentClass) : ScriptRegistrator()
{
	this->parentClass = pParentClass;
}
BaseScriptRegistrator::~BaseScriptRegistrator() {}

__int64 BaseScriptRegistrator::Register(__int64 a2)
{
	if ((*(uint32_t*)(a2 + 24) & 0x10) == 0)
		return 1;

	Debugln("Base registrator called.");

	if(!fRegisterClass) return 1; // script engine not initialized? how did this function get called?!
	if (!fRegisterClassStaticFunction) return 1; // ???

	ScriptContext* pContext = *(ScriptContext**)(a2 + 16);
	const char* classnamecstr = this->parentClass->GetName();
	Debugln("Registering class '%s'.", classnamecstr);
	ClassInstance* pClass = fRegisterClass(pContext, classnamecstr);
	
	this->pClass = pClass; //*(ClassInstance**)(a1 + 24) = pClass;

	if (pClass)
	{
		// register functions
		pContext = *(ScriptContext**)(a2 + 16); // game shows us regrabbing this value so we'll do that to be safe

		// lambda function so register calls registration method and takes in this context and class
		auto registerFunc =  [&pContext, &pClass](const char* fName, void* fPtr) {
			auto res = fRegisterClassStaticFunction(pContext, pClass, fName, (Enscript__Function)fPtr, 0, 1);
			return (res != NULL);
		};

		parentClass->RegisterFunctions(registerFunc);
	}

	return 1;
}
