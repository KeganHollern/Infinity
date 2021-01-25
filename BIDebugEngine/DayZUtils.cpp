#pragma once
#include "pch.h"

#include <stdio.h>
#include <string>

#include "types.h"
#include "DayZUtils.h"

CONSOLEPRINT DayZ::Utils::Internal::dayzConsolePrint;

void DayZ::Utils::PrintToConsole(const char* format, ...)
{
	if (!Internal::dayzConsolePrint)
	{
		printf("(E) PrintToConsole: Failed to print to console. | DayZ method not found!");
		
		//print
		va_list argptr;
		va_start(argptr, format);
		vfprintf(stdout, format, argptr);
		va_end(argptr);
		return;
	}
	else
	{
		//format into buffer
		char buffer[1024];
		va_list argptr;
		va_start(argptr, format);
		vsprintf(buffer, format, argptr);
		va_end(argptr);

		//print
		Internal::dayzConsolePrint(buffer, NULL); //try passing NULL ?
	}
}