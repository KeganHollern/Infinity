#include <stdio.h>
#include <stdint.h>
#include <Plugins.h>
#include <PluginTypes.h>
#include <combaseapi.h>
#include <string>

#include "ExamplePlugin.h"

namespace Framework = Infinity::Enfusion::Enscript::Framework;
namespace Enscript = Infinity::Enfusion::Enscript;


//proto void SetStringValue(out string result, string new_value, bool use_memcpy = false);
void SetStringValue(Enscript::FunctionContext* pContext, Enscript::FunctionResult* pResult)
{
	if (!pContext) return;
	if (!pContext->GetArgument(0)) return;
	if (!pContext->GetArgument(1)) return;
	if (!pContext->GetArgument(2)) return;

	//this does not crash
	if (pContext->GetArgument(2)->Value)
	{
		const char* input_value = (const char*)pContext->GetArgument(1)->Value;
		size_t length = strlen(input_value);
		memcpy(pContext->GetArgument(0)->Value, input_value, length);
		*((char*)pContext->GetArgument(0)->Value + length) = 0; //gotta add a string terminator :)
	}
	else
		pContext->GetArgument(0)->Value = pContext->GetArgument(1)->Value;
}

//proto string GetValueBack(string val);
Enscript::NativeArgument* GetValueBack(Enscript::FunctionContext* pContext, Enscript::FunctionResult* pResult)
{
	if (!pContext) return pResult->Result;
	if (!pContext->GetArgument(0)) return pResult->Result;

	const char* input_value = (const char*)pContext->GetArgument(0)->Value;
	size_t length = strlen(input_value);

	memcpy(pResult->Result->Value, input_value, length);
	*((char*)pResult->Result->Value + length) = 0; //gotta add a string terminator :)
	return pResult->Result;
}


//proto bool CreateGuid(out string guid);
Enscript::NativeArgument* CreateGuid(Enscript::FunctionContext* pContext, Enscript::FunctionResult* pResult)
{
	*((bool*)pResult->Result) = false; //default the value to false

	if (!pContext) return pResult->Result;
	if (!pContext->GetArgument(0)) return pResult->Result;

	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	if (hr == S_OK)
	{
		wchar_t* guidString;
		hr = StringFromCLSID(guid, &guidString);
		if (hr == S_OK)
		{
			//convert wide string to string
			std::wstring wstr = guidString;
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
			std::string str(size_needed, 0);
			WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);

			//--- set value in DayZ
			memcpy(pContext->GetArgument(0)->Value, str.c_str(), str.length());
			*((char*)pContext->GetArgument(0)->Value + str.length()) = 0; //gotta add a string terminator :)
			*((bool*)pResult->Result) = true;
		}
	}

	Infinity::Logging::Println ("Returning Result!");
	return pResult->Result;
}


/* if this was a standalone plugin the following function would be | void __declspec(dllexport) OnPluginLoad() */
void SetValuePluginInit()
{
	Infinity::Enfusion::Enscript::RegisterFunction("SetStringValue", &SetStringValue);
	Infinity::Enfusion::Enscript::RegisterFunction("GetValueBack", &GetValueBack);
	Infinity::Enfusion::Enscript::RegisterFunction("CreateGuid", &CreateGuid);
	Infinity::Logging::Println("SetValue Plugin Loaded.");
}