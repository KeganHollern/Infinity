
#include <string>
#include <stdint.h>

#include "ScriptEngine.h"
#include "ScriptRegistrator.h"


ScriptRegistrator::ScriptRegistrator() 
{
	pModuleName = *g_pStringModuleGame;
	pNext = NULL;
}
ScriptRegistrator::~ScriptRegistrator() {
	printf("uh oh! unsafe deconstruct!\n");
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


__int64 UndefinedFunction(__int64* a1, __int64* a2)
{
	printf("undefined function\n");
	return 0;
}

BaseScriptRegistrator::BaseScriptRegistrator(std::string name) : ScriptRegistrator() 
{
	this->className = name;
}
BaseScriptRegistrator::~BaseScriptRegistrator() {}

__int64 BaseScriptRegistrator::Register(__int64 a2)
{
	if ((*(uint32_t*)(a2 + 24) & 0x10) == 0)
		return 1;

	printf("base register called.\n");

	if(!fRegisterClass) return 1; // script engine not initialized? how did this function get called?!
	if (!fRegisterClassStaticFunction) return 1; // ???

	ScriptContext* pContext = *(ScriptContext**)(a2 + 16);
	const char* classnamecstr = this->className.c_str();
	printf("registering class '%s'.\n", classnamecstr);
	ClassInstance* pClass = fRegisterClass(pContext, classnamecstr);
	
	this->pClass = pClass; //*(ClassInstance**)(a1 + 24) = pClass;

	if (pClass)
	{
		// register functions
		pContext = *(ScriptContext**)(a2 + 16); // game shows us regrabbing this value so we'll do that to be safe
		printf("registering class function 'Undefined'.\n");
		fRegisterClassStaticFunction(pContext, pClass, "Undefined", &UndefinedFunction, 0, 1);
	}

	return 1;
}
