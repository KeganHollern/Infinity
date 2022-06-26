#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "infinity.h"
#include "dayz.h"
#include "reforger.h"
#include "engine.h"

#include "console.hpp"

Infinity::Engine* Infinity::g_pEngine;

void Infinity::Entry()
{
	// if no console, create one
	if (!GetConsoleWindow() && IsDebug())
	{
		if (AllocConsole())
		{
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
		}
	}


	Println("Initializing infinity.");

	//TODO: determine what game we're in and construct the engine for that game
	g_pEngine = new Reforger();

	// this will initialize all hooks. hook will handle loading plugins
	g_pEngine->Init();

	Println("Initialization complete.");
}