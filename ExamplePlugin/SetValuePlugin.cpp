#include "pch.h"

#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;
namespace Enscript = Infinity::Enfusion::Enscript;

char* CreateEnforceString(const char* str);


//proto native void SetABCs(out string a, out string b, out string c);
//proto native void SetABCs2(out string a, out string b, out string c);

void SetABCs(Enscript::FunctionContext* pContext, void* pUnk)
{
	if (!pContext)
		return;
	if (!pContext->GetArgument(0))
		return;
	if (!pContext->GetArgument(1))
		return;
	if (!pContext->GetArgument(2))
		return;

	pContext->GetArgument(0)->Value = CreateEnforceString("a");
	pContext->GetArgument(1)->Value = CreateEnforceString("b");
	pContext->GetArgument(2)->Value = CreateEnforceString("c");
}
void SetABCs2(Enscript::FunctionContext* pContext, void* pUnk)
{
	if (!pContext)
		return;
	if (!pContext->GetArgument(0))
		return;
	if (!pContext->GetArgument(1))
		return;
	if (!pContext->GetArgument(2))
		return;
	

	Infinity::Enfusion::Enscript::SetStringArgumentValue(pContext, 0, (char*)"a", false);
	Infinity::Enfusion::Enscript::SetStringArgumentValue(pContext, 1, (char*)"b", false);
	Infinity::Enfusion::Enscript::SetStringArgumentValue(pContext, 2, (char*)"c", false);
}

/*
When setting a value in enforce, we need to allocate space for it using enfusion.
this method takes a string & allocates just enough space for it to sit in
*/
char* CreateEnforceString(const char* str)
{
	size_t size = strlen(str) + 1;
	char* safe_ptr = (char*)Infinity::Enfusion::MemAlloc(size);
	strcpy_s(safe_ptr, size, str);
	return safe_ptr;
}

/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void SetValuePluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("SetABCs", &SetABCs);
	Infinity::Enfusion::Enscript::RegisterFunction("SetABCs2", &SetABCs2);
	Infinity::Logging::Print("SetValue Plugin Loaded.");
}