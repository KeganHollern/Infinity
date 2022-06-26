

#include <Windows.h>

#include "patterns.h"
#include "console.hpp"

#include "engine.h"

int Infinity::Engine::ApplyHook(void* address, void* method, void** original)
{
	MH_STATUS status = MH_CreateHook(address, method, original);

	if (status == MH_OK)
		status = MH_EnableHook(address);
	else
		Errorln("Failed to apply hook.");

	return status;
}
void* Infinity::Engine::FindFunction(const char* name, std::string pattern, int offset)
{
	if (pattern == "")
		return NULL;
	void* address = Infinity::FindPattern(pattern, GetModuleHandle(NULL), offset);
	if (!address)
		Errorln("Failed to find function '%s'.", name);

	return address;
}