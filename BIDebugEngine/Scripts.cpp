#pragma once
#include "pch.h"

#include <stdint.h>
#include <stdio.h>
#include <string>

#include "types.h"
#include "Scripts.h"
#include "Patterns.h"
#include "RVExtension.h"
#include "Plugins.h"
#include "DayZUtils.h"

INITMODULES DayZ::Scripts::Internal::dayzInitModules;
ADDFUNCTION DayZ::Scripts::Internal::dayzRegisterFunction;
GETTYPENAME DayZ::Scripts::Internal::dayzGetTypeFunction;
ADDCLASSFUNCTION DayZ::Scripts::Internal::dayzRegisterClassFunction;
RUNFUNCTIONONNEWTHREAD DayZ::Scripts::Internal::dayzRunFunction;

bool DayZ::Scripts::RunFunction(void* pObject, const char* function, int64_t arg4)
{
	if (!Internal::dayzRunFunction)
	{
		printf("(E) RunFunction: Could not run %s | Could not find dayz method!\n", function);
		return false;
	}
	if (!pObject)
	{
		printf("(E) RunFunction: Could not run %s | NULL Object Provided!\n", function);
		return false;
	}

	int64_t result;
	int64_t* pResult = Internal::dayzRunFunction(pObject, &result, (char*)function, arg4);
	printf("Function Ran. Result: %p\n", pResult);
	return true;
}
uint64_t* DayZ::Scripts::RegisterGlobal(void* pThis, const char* name, void* function)
{
	if (!Internal::dayzRegisterFunction)
	{
		printf("(E) RegisterGlobal: Could not register %s @ %p | Could not find dayz method!\n", name, function);
		return NULL;
	}
	if (!pThis)
	{
		printf("(E) RegisterGlobal: Could not register %s @ %p | Script Module was NULL!\n", name, function);
		return NULL;
	}
	//printf("Register: Registering %s @ %p...\n", name, function);
	int32_t flag = 0;
	return Internal::dayzRegisterFunction(pThis, name, function, flag);
}
uint64_t* DayZ::Scripts::RegisterObject(void* pThis, const char* name)
{
	if (!Internal::dayzGetTypeFunction)
	{
		printf("(E) RegisterObject: Could not register %s | Could not find dayz method!\n", name);
		return NULL;
	}
	if (!pThis)
	{
		printf("(E) RegisterObject: Could not register %s | Script Module was NULL!\n", name);
		return NULL;
	}

	GETTYPE_RESULT result;
	char mode = 2;
	GETTYPE_RESULT* resultant_value = Internal::dayzGetTypeFunction(pThis, &result, name, mode);
	if (resultant_value)
	{
		return resultant_value->pType;
	}
	else
	{
		printf("(E) RegisterObject: Failed to register %s | DayZ method returned NULL!\n", name);
		return NULL;
	}
}
uint64_t* DayZ::Scripts::FindObject(void* pThis, const char* name) {
	if (!Internal::dayzGetTypeFunction)
	{
		printf("(E) RegisterObject: Could not register %s | Could not find dayz method!\n", name);
		return NULL;
	}
	if (!pThis)
	{
		printf("(E) RegisterObject: Could not register %s | Script Module was NULL!\n", name);
		return NULL;
	}

	GETTYPE_RESULT result;
	char mode = 1;
	GETTYPE_RESULT* resultant_value = Internal::dayzGetTypeFunction(pThis, &result, name, mode);
	if (resultant_value)
	{
		return resultant_value->pType;
	}
	else
	{
		printf("(E) RegisterObject: Failed to register %s | DayZ method returned NULL!\n", name);
		return NULL;
	}
}
uint64_t* DayZ::Scripts::Register(void* pThis, void* pParent, const char* name, void* function, bool use_special_stack)
{
	if (!Internal::dayzRegisterClassFunction)
	{
		printf("(E) Register: Could not register %s @ %p | Could not find dayz method!\n", name, function);
		return NULL;
	}
	if (!pThis)
	{
		printf("(E) Register: Could not register %s @ %p | Script Module was NULL!\n", name, function);
		return NULL;
	}
	if (!pParent)
	{
		printf("(E) Register: Could not register %s @ %p | Parent Type was NULL!\n", name, function);
		return NULL;
	}
	int32_t stack_type = use_special_stack ? 0x2000 : 0;
	char mode = 1;
	return Internal::dayzRegisterClassFunction(pThis, pParent, name, function, stack_type, mode);
}
uint64_t* DayZ::Scripts::InitModules(void* pThis)
{
	uint64_t* result = Internal::dayzInitModules(pThis);
	//we want to register our functions later
	printf("InitModules: Initializing modules...\n");

	RegisterGlobal(pThis, "CallDZ", &RVExt::callExt_DZ);
	RegisterGlobal(pThis, "CallRVVer", &RVExt::callExt_RVVer);
	RegisterGlobal(pThis, "CallRV", &RVExt::callExt_RV);
	RegisterGlobal(pThis, "CallRVArgs", &RVExt::callExt_RVArgs);

	Infinity::PluginSystem::LoadPlugins(pThis); //load any plugins and register their function

	return result;
}