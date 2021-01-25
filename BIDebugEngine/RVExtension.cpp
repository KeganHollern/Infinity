#include "pch.h"

#include <stdexcept>

#include "RVExtension.h"

HMODULE RVExt::GetExtension(char* library)
{
	char* module_name = new char[255];
	if (sprintf_s(module_name, 255, "%s.dll", library) < 0)
		return NULL;

	HMODULE module = GetModuleHandleA(module_name);

	//library is not loaded
	if (module == NULL)
		module = LoadLibraryA(module_name);

	delete[] module_name;

	return module;
}

char* RVExt::callExt_DZ(char* library, char* function, char* argument)
{
	HMODULE module = GetExtension(library);

	//library does not exist
	if (module == NULL)
		return (char*)"Extension not found";

	printf("DZExtension Call\n");
	printf("\tLibrary: %s\n", library);
	printf("\tFunction: %s\n", function);
	printf("\tArgument: %s\n", argument);

	//extract all possible exports
	DZExtensionFunction DZExtension = (DZExtensionFunction)GetProcAddress(module, "DZExtension");

	if (DZExtension == NULL)
		return (char*)"Extension does not contain DZExtension export";
	if (DZExtension)
		return DZExtension(function, argument);
	else
		return (char*)"";
}
char* RVExt::callExt_RVArgs(char* library, char* function, const char** args, int argsCount)
{
	HMODULE module = GetExtension(library);

	//library does not exist
	if (module == NULL)
		return (char*)"Extension not found";

	DWORD64* argptr = (DWORD64*)args;
	argptr += 0x5; //28 bytes off of base ptr

	const char** arg_arr = (const char**)(*(DWORD64*)argptr);//deref and cast


	printf("RVExtensionArgs Call\n");
	printf("\tLibrary: %s\n", library);
	printf("\tFunction: %s\n", function);
	for (int i = 0; i < argsCount; i++)
		printf("\tArgument[%i]: %s\n", i, arg_arr[i]);

	RVExtensionArgsFunction RVExtensionArgs = (RVExtensionArgsFunction)GetProcAddress(module, "RVExtensionArgs");
	char buffer[10240] = "";
	if (RVExtensionArgs)
	{
		RVExtensionArgs(buffer, 10240, function, arg_arr, argsCount);
		printf("\tResult: %s\n", buffer);
	}
	else
	{
		printf("Error: Failed to find RVExtensionArgs export in the library!\n");
	}
	return buffer;
}
char* RVExt::callExt_RV(char* library, char* function)
{
	HMODULE module = GetExtension(library);

	//library does not exist
	if (module == NULL)
		return (char*)"Extension not found";

	printf("RVExtension Call\n");
	printf("\tLibrary: %s\n", library);
	printf("\tFunction: %s\n", function);

	RVExtensionFunction RVExtension = (RVExtensionFunction)GetProcAddress(module, "RVExtension");
	char buffer[10240] = "";
	if (RVExtension)
	{
		RVExtension(buffer, 10240, function);
		printf("\tResult: %s\n", buffer);
	}
	else
	{
		printf("Error: Failed to find RVExtension export in the library!\n");
	}

	return buffer;
}
char* RVExt::callExt_RVVer(char* library)
{
	HMODULE module = GetExtension(library);

	//library does not exist
	if (module == NULL)
		return (char*)"Extension not found";

	printf("RVExtensionVersion Call\n");
	printf("\tLibrary: %s\n", library);

	RVExtensionVersionFunction RVExtensionVersion = (RVExtensionVersionFunction)GetProcAddress(module, "RVExtensionVersion");
	char buffer[32] = "";
	if (RVExtensionVersion)
	{
		RVExtensionVersion(buffer, 32);
		printf("\tResult: %s\n", buffer);
	}
	else
	{
		printf("Error: Failed to find RVExtensionVersion export in the library!\n");
	}
	return buffer;
}
