#include <string.h>
#include <Windows.h>
#include <Psapi.h>
#include <sstream>

#include "Console.hpp"

#include "Patterns.h"

unsigned int GetHexVal(unsigned char hex_val);
unsigned char HexToByte(std::string val);
bool check_match(char* address, const char* pattern, const char* mask);
void* findPatternMask(const char* pattern, const char* mask, HMODULE module, int offset);


void* FindPattern(std::string bn_pattern, HMODULE module, int offset)
{
	//char moduleName[255];
	//GetModuleBaseNameA(GetCurrentProcess(), module, moduleName, 255);
	//std::cout << "Find Pattern called on " << moduleName << std::endl;

	//example pattern: 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 4C 8B 8B ? ? ? ?
	//std::cout << "Converting Binary Ninja Pattern: " << std::endl << "\tPattern: " << bn_pattern << std::endl;

	std::stringstream converter;
	std::istringstream f(bn_pattern);
	std::string s;
	char mask[255] = { 0 };
	unsigned char pattern[255] = { 0 };
	int i = 0;
	while (std::getline(f, s, ' ')) {

		//s will be 48, 89, 5C, ... ect.

		if (s[0] == '?') //? entry means skip
		{
			unsigned char val = 0x0;
			pattern[i] = val;
			mask[i] = '?';
		}
		else
		{
			unsigned char val = HexToByte(s);
			//valid entry, convert from "A0" to '\xA0'
			pattern[i] = val;
			mask[i] = 'x';
		}
		i++;
	}

	return findPatternMask((const char*)pattern, mask, module, offset);

}

void* findPatternMask(const char* pattern, const char* mask, HMODULE module, int offset)
{
	MODULEINFO info;
	if (!GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO)))
	{
		Errorln("Failed to get module information during pattern scan.");
		return NULL;
	}

	void* base = info.lpBaseOfDll;
	DWORD size = info.SizeOfImage;
	//probably better hueristics to improve this performance but meh
	for (uint64_t i = 0; i < size; i++)
	{
		void* addr = (void*)((uint64_t)base + i);
		if (check_match((char*)addr, pattern, mask))
			return (void*)((uint64_t)addr + offset);
	}
	return NULL;
}


bool check_match(char* address, const char* pattern, const char* mask)
{
	int min = strlen(mask); //can't use strlen on pattern because it returns a value ending at the first 0x0
	for (int i = 0; i < min; i++)
	{
		char a = address[i];
		char b = pattern[i];
		char m = mask[i];
		if (m == '?')
			continue;
		if (a != b)
			return false;
	}
	return true;
}

unsigned char HexToByte(std::string val)
{
	if (val.length() != 2)
		return 0x00; //error!

	char a = val[0];
	char b = val[1];

	unsigned int val_a = GetHexVal(a) * 16;
	unsigned int val_b = GetHexVal(b);

	unsigned int total = val_a + val_b;

	return total;
}
// this is just pain
unsigned int GetHexVal(unsigned char hex_val)
{
	switch (hex_val)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	}
	return 0;
}