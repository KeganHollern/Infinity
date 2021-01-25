#pragma once
#include "pch.h"

#include <stdint.h>
#include <string>
#include <stdio.h>
#include <MinHook.h>
#include <vector>
#include <algorithm>

#include "types.h"
#include "DayZUtils.h"
#include "Scripts.h"
#include "Patterns.h"
#include "Engine.h"

void* FindFunction(const char* name, std::string pattern, int offset = 0);
MH_STATUS ApplyHook(void* address, void* method, void** original);

std::string INITMODULES_BINARYNINJA_PATTERN = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 4C 8B 8B ? ? ? ?";
std::string REGISTERGLOBALFUNCTION_BINARYNINJA_PATTERN = "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 41 8B F1 48 8B E9"; //global function registration
std::string GETOBJECTTYPEFUNCTION_BINARYNINJA_PATTERN = "48 8B C4 44 88 48 ? 4C 89 40 ? 48 89 50 ? 48 89 48 ? 53";
std::string REGISTERFUNCTION_BINARYNINJA_PATTERN = "48 89 74 24 ? 57 48 83 EC ? 0F B6 44 24 ?";
std::string PRINTTOCONSOLE_BINARYNINJA_PATTERN = "48 89 5C 24 ? 56 48 81 EC ? ? ? ? 80 3D ? ? ? ? ?";
std::string RUNFUNCTIONONNEWTHREAD_BINARYNINJA_PATTERN = "4C 89 44 24 ? 4C 89 4C 24 ? 53 56 57 48 83 EC ? 48 8B DA 48 8D 74 24 ? 48 8B F9 49 8B D0";
std::string GETPROFILEPATH_BINARYNINJA_PATTERN = "48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 83 CB FF";
std::string GLOBAL_FILEHANDLER_BINARYNINJA_PATTERN = "48 89 0D ? ? ? ? 4C 8D 0D ? ? ? ?";
std::string REGISTERPATHKEY_BINARYNINJA_PATTERN = "4C 89 4C 24 ? 55 53 56 41 54";
std::string ISVALIDFORMODE_BINARYNINJA_PATTERN = "48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 8B FA"; //first method called in OpenFile script func
std::string FILEHANDLER_CANACCESSFILE_BINARYNINJA_PATTERN = "48 83 EC ? 48 8B CA FF 15 ? ? ? ?";

GETPROFILEPATH DayZ::Engine::Internal::dayzGetProfilePath;
void** DayZ::Engine::Internal::dayzFileHandlerPtr;
REGISTERPATHKEY DayZ::Engine::Internal::dayzRegisterPathKey;
ISVALIDFORMODE DayZ::Engine::Internal::dayzIsValidForMode;
CANACCESSFILE DayZ::Engine::Internal::dayzCanAccessFile;
std::vector<std::string> DayZ::Engine::Internal::allow_write_path_keys;

bool DayZ::Engine::HookInit() {
	//--- initialize functions we'll need to call internally
	DayZ::Scripts::Internal::dayzRegisterFunction = (ADDFUNCTION)FindFunction("global register", REGISTERGLOBALFUNCTION_BINARYNINJA_PATTERN);
	DayZ::Scripts::Internal::dayzGetTypeFunction = (GETTYPENAME)FindFunction("type register", GETOBJECTTYPEFUNCTION_BINARYNINJA_PATTERN);
	DayZ::Scripts::Internal::dayzRegisterClassFunction = (ADDCLASSFUNCTION)FindFunction("class register", REGISTERFUNCTION_BINARYNINJA_PATTERN);
	DayZ::Scripts::Internal::dayzRunFunction = (RUNFUNCTIONONNEWTHREAD)FindFunction("run on new thread", RUNFUNCTIONONNEWTHREAD_BINARYNINJA_PATTERN);

	DayZ::Engine::Internal::dayzRegisterPathKey = (REGISTERPATHKEY)FindFunction("register path key", REGISTERPATHKEY_BINARYNINJA_PATTERN);
	DayZ::Engine::Internal::dayzGetProfilePath = (GETPROFILEPATH)FindFunction("get profile path", GETPROFILEPATH_BINARYNINJA_PATTERN);
	//-- this global variable needs to be pulled from a relative operation
	void* filehandler_rel_addr = Patterns::FindBinaryNinjaPattern(GLOBAL_FILEHANDLER_BINARYNINJA_PATTERN, GetModuleHandle(NULL), 3);
	DWORD offset_value = *(DWORD*)filehandler_rel_addr;
	DayZ::Engine::Internal::dayzFileHandlerPtr = (void**)((uint64_t)filehandler_rel_addr + 0x4 + offset_value);
	if (IsBadReadPtr(DayZ::Engine::Internal::dayzFileHandlerPtr, 0x8))
	{
		printf("(E) HookInit: Failed to find FileHandler Offset!\n");
		DayZ::Engine::Internal::dayzFileHandlerPtr = NULL;
	}

	DayZ::Utils::Internal::dayzConsolePrint = (CONSOLEPRINT)FindFunction("console print", PRINTTOCONSOLE_BINARYNINJA_PATTERN);
	

	
	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
	{
		printf("(E) HookInit: Failed to initialize MinHook\n");
		return false;
	}
	//--- hook initmodules so we can register custom scripts
	void* address = FindFunction("init modules", INITMODULES_BINARYNINJA_PATTERN);
	status = ApplyHook(address, &DayZ::Scripts::InitModules, reinterpret_cast<LPVOID*>(&DayZ::Scripts::Internal::dayzInitModules));
	if (status != MH_OK)
	{
		printf("(E) HookInit: Failed to create InitModules hook\n");
		return false; //this is breaking for our library, so we'll need to terminate here
	}
	printf("HookInit: Successfully hooked InitModules @ %p\n", address);

	address = FindFunction("file handler can access file", FILEHANDLER_CANACCESSFILE_BINARYNINJA_PATTERN);
	status = ApplyHook(address, &DayZ::Engine::CanAccessFile, reinterpret_cast<LPVOID*>(&DayZ::Engine::Internal::dayzCanAccessFile));
	if (status != MH_OK)
	{
		printf("(E) HookInit: Failed to create CanAccessFile hook\n");
	}
	else
	{
		printf("HookInit: Successfully hooked CanAccessFile @ %p\n", address);
	}
	//--- hook IsValidForMode so we can enable write to custom directories
	address = FindFunction("is valid for mode", ISVALIDFORMODE_BINARYNINJA_PATTERN);
	status = ApplyHook(address, &DayZ::Engine::IsValidForMode, reinterpret_cast<LPVOID*>(&DayZ::Engine::Internal::dayzIsValidForMode));
	if (status != MH_OK)
	{
		printf("(E) HookInit: Failed to create InitModules hook\n");
	}
	else
	{
		printf("HookInit: Successfully hooked IsValidForMode @ %p\n", address);
	}

	DayZ::Utils::PrintToConsole("Infinity Loaded!"); //console isn't open at this time so it's kinda useless to do this
	return true;
}

int64_t DayZ::Engine::CanAccessFile(void* pHandle, LPCSTR filepath)
{
	int64_t valid_result = Internal::dayzCanAccessFile(pHandle, filepath);	
	return valid_result;
}

bool DayZ::Engine::GetProfilePath(char* pResult)
{
	if (!Internal::dayzGetProfilePath)
	{
		printf("(E) GetProfilePath: Failed to get profile path | Could not find dayz method!\n");
		return false;
	}
	return Internal::dayzGetProfilePath(pResult);
}

void* DayZ::Engine::GetFileHandler()
{
	if (!Internal::dayzFileHandlerPtr)
	{
		printf("(E) GetFileHandler: Failed to get file handler | Could not find dayz method!\n");
		return NULL;
	}
	return *Internal::dayzFileHandlerPtr;
}

void DayZ::Engine::RegisterPathKey(void* pFileHandler, const char* path, const char* key, bool allow_write)
{
	if (!Internal::dayzRegisterPathKey)
	{
		printf("(E) RegisterPathKey: Failed to register key %s for path %s | Could not find dayz method!\n", key, path);
		return;
	}
	int32_t flag = 0;
	int32_t flag1 = 0x76d;
	int64_t flag2 = 0;
	bool pResult = Internal::dayzRegisterPathKey(pFileHandler, (char*)path, flag, (char*)key, flag1, flag2);
	if (pResult)
	{
		if (allow_write)
		{
			Internal::allow_write_path_keys.push_back(std::string(key));
			printf("Successfully Registerd WRITE Key %s for Path %s\n", key, path);
		}
		else
			printf("Successfully Registerd READ ONLY Key %s for Path %s\n", key, path);
	}
	else
	{
		printf("Failed to register key %s for path %s\n", key, path);
	}
}

bool DayZ::Engine::IsValidForMode(char* filepath, int32_t mode)
{
	int32_t new_mode = mode;
	std::string path_str(filepath);
	if (path_str.find_first_of('$', 0) == 0)
	{
		size_t index = path_str.find_first_of(':', 0);
		if (index != std::string::npos && index > 1) //$: is invalid
		{
			//is a valid $[something]:...
			std::string key = path_str.substr(1, index - 1); //$[value]:
			if (std::find(Internal::allow_write_path_keys.begin(), Internal::allow_write_path_keys.end(), key) != Internal::allow_write_path_keys.end())
			{
				//our key exists in our registered write key list!
				new_mode = 1;
			}
		}
	}
	return Internal::dayzIsValidForMode(filepath, new_mode);
}

MH_STATUS ApplyHook(void* address, void* method, void** original)
{
	MH_STATUS status = MH_CreateHook(address, method, original);
	if (status == MH_OK)
	{
		status = MH_EnableHook(address);
	}
	return status;
}
void* FindFunction(const char* name, std::string pattern, int offset)
{
	if (pattern == "")
		return NULL;

	//printf("FindFunction: Searching for %s function...\n", name);
	void* address = Patterns::FindBinaryNinjaPattern(pattern, GetModuleHandle(NULL), offset);
	if (!address)
		printf("(E) FindFunction: Failed to find %s function!\n", name);
	//else
		//printf("FindFunction: Found %s function @ %p\n", name, address);
	
	return address;
}