#pragma once
#include "pch.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>

#include "Console.h"

bool Console::ToFile()
{
	/*
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
	*/
	freopen("debug_engine.log", "w", stdout);
	freopen("debug_engine.log", "w", stderr);
	return true;
}
bool Console::Create()
{
	if (!AllocConsole())
	{
		FILE* hFile = std::fopen("error.BIDebugEngine.log", "w");
		if (hFile)
		{
			std::fprintf(hFile, "Failed to allocate console!");
			std::fclose(hFile);
		}
		return false;
	}


	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	return true;
}
