#pragma once
#include "pch.h"
#include "Utils.h"

#include <cstring>

bool Utils::IsDebug()
{
#ifdef _DEBUG
	return true;
#else
	char* cmd = GetCommandLineA();
	return IsPartOf("rvdbg", cmd); //looking for -rvdbg in command line params
#endif
}
bool Utils::IsPartOf(const char* a, char* b) {
	if (std::strstr(b, a) != NULL) {    //Strstr says does b contain a
		return true;
	}
	return false;
}
