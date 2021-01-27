#include "pch.h"

#include <stdexcept>
#include <filesystem>

#include "RVExtension.h"

namespace fs = std::filesystem;


HMODULE RVExt::GetExtension(const char* library)
{
	//1. get cannonical path to library
	fs::path library_path = std::string(library) + ".dll"; //extension system doesn't include dll @ the end of the library name
	fs::path canonical_path = fs::canonical(library_path);
	fs::path filename = canonical_path.filename();

	//2. if the library doesn't exist ignore
	if (!fs::exists(canonical_path))
		return NULL;

	HMODULE hModule = GetModuleHandleW(filename.c_str());

	if (!hModule)
		hModule = LoadLibraryW(canonical_path.c_str());

	return hModule;
}
char* RVExt::callExt_DZ(char* library, char* function, char* argument)
{
	HMODULE hLibrary = GetExtension(library);
	if (!hLibrary)
		return (char*)"Extension not found";

	DZExtensionFunction DZExtension = (DZExtensionFunction)GetProcAddress(hLibrary, "DZExtension");
	if (!DZExtension)
		return (char*)"Extension does not contain DZExtension export";

	printf("DZExtension Call\n\tLibrary: %s\n\tFunction: %s\n\tArgument: %s\n", library, function, argument);
	return DZExtension(function, argument); //we expect that this extension will handle allocating memory properly
	
	
}
char* RVExt::callExt_RVArgs(char* library, char* function, const char*** args, int argsCount)
{
	// sanity check arguments
	if (!args)
		return (char*)"No argument array provided";
	const char*** internal_structure = args + 0x5; //28 bytes off of base ptr ???
	if (IsBadReadPtr(internal_structure, sizeof(void*)))
		return (char*)"Invalid arguments array provided!";

	const char** arg_arr = *internal_structure;

	if (!arg_arr)
		return (char*)"Invalid arguments array provided!";

	HMODULE hLibrary = GetExtension(library);
	if (!hLibrary)
		return (char*)"Extension not found";
	RVExtensionArgsFunction RVExtensionArgs = (RVExtensionArgsFunction)GetProcAddress(hLibrary, "RVExtensionArgs");
	if (!RVExtensionArgs)
		return (char*)"Extension does not contain RVExtensionArgs export";
	
	printf("RVExtensionArgs Call\n");
	printf("\tLibrary: %s\n", library);
	printf("\tFunction: %s\n", function);
	for (int i = 0; i < argsCount; i++)
		printf("\tArgument[%i]: %s\n", i, arg_arr[i]);

	char* buffer = new char[MAX_BUFFER_SIZE];
	RVExtensionArgs(buffer, MAX_BUFFER_SIZE, function, arg_arr, argsCount);
	printf("\tResult: %s\n", buffer);

	/*
	in order to save memory usage, we'll copy the result from RVExtensionArgs into a new buffer that is just large enough
	this will shrink our memory leak down from 10kb per call to whatever the resultant string size is
	*/
	size_t output_size = strlen(buffer);
	char* result = new char[output_size+1];
	if(output_size > 0) //only copy if we actually have data to copy
		strcpy_s(result, output_size, buffer); 
	delete[] buffer;
	return result;
}
char* RVExt::callExt_RV(char* library, char* function)
{
	HMODULE hLibrary = GetExtension(library);
	if (!hLibrary)
		return (char*)"Extension not found";
	RVExtensionFunction RVExtension = (RVExtensionFunction)GetProcAddress(hLibrary, "RVExtension");
	if (!RVExtension)
		return (char*)"Extension does not contain RVExtension export";

	printf("RVExtension Call\n");
	printf("\tLibrary: %s\n", library);
	printf("\tFunction: %s\n", function);

	char* buffer = new char[MAX_BUFFER_SIZE];
	RVExtension(buffer, MAX_BUFFER_SIZE, function);
	printf("\tResult: %s\n", buffer);

	size_t output_size = strlen(buffer);
	char* result = new char[output_size + 1];
	if (output_size > 0) //only copy if we actually have data to copy
		strcpy_s(result, output_size, buffer);
	delete[] buffer;
	return result;
}
char* RVExt::callExt_RVVer(char* library)
{
	HMODULE hLibrary = GetExtension(library);
	if (!hLibrary)
		return (char*)"Extension not found";
	RVExtensionVersionFunction RVExtensionVersion = (RVExtensionVersionFunction)GetProcAddress(hLibrary, "RVExtensionVersion");
	if (!RVExtensionVersion)
		return (char*)"Extension does not contain RVExtensionVersion export";

	char buffer[32] = "";
	RVExtensionVersion(buffer, sizeof(buffer));
	printf("\tResult: %s\n", buffer);

	size_t output_size = strlen(buffer);
	char* result = new char[output_size + 1];
	if (output_size > 0) //only copy if we actually have data to copy
		strcpy_s(result, output_size, buffer);

	return result;
}