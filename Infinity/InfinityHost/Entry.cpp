#include <chrono>
#include <thread>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "ScriptRegistrator.h"
#include "ScriptEngine.h"

#include "Entry.h"


Infinity globalobj; // hold infinity in memory indefinitely
const std::string sModuleName = "ModuleGame";

void start(Infinity* g_pInfinity);

Infinity::Infinity() : startup(start, this) {}
Infinity::~Infinity()
{
	startup.join();
}

void Infinity::Init()
{
	// find all of our offsets
	if (!InitScriptEngine())
	{
		printf("failed to init script engine\n");
		return;
	}
	if (!g_pGlobalRegistrator)
	{
		printf("global script registrator address null?\n");
		return;
	}

	printf("infinity initialized\n");
}
void Infinity::LoadPlugins()
{
	printf("constructing new registrator\n");
	BaseScriptRegistrator* g_GlobalClass = new BaseScriptRegistrator("InfinityTest");
	printf("registering %p\n", g_GlobalClass);
	ScriptRegistrator* last = (*g_pGlobalRegistrator)->GetLast();
	printf("last element %p\n", last);
	last->Insert(g_GlobalClass);

	if (!(*g_pGlobalRegistrator)->HasChild(g_GlobalClass))
	{
		printf("??? not found in registration table!?");
	}
	else
	{
		printf("registered!\n");
	}
}


// this is the main entrypoint for our library.
// it runs on it's own thread
void start(Infinity* g_pInfinity)
{
	// if no console, create one
	if (!GetConsoleWindow())
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

	printf("Infinity startup");

	g_pInfinity->Init();

	// wait until the global registrator head is inserted & anything with ModuleGame exists
	auto start = std::chrono::steady_clock::now();
	bool found = false;
	while (!*g_pGlobalRegistrator || !found)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		ScriptRegistrator* pCheck = *g_pGlobalRegistrator;
		if (!pCheck) continue;

		do
		{
			if (!pCheck) break;
			const char* name = pCheck->GetName();

			if (std::string(name) == sModuleName)
			{
				g_pStringModuleGame = &name; // save the pointer to `ModuleGame` so we can use it to construct our own registrators
				printf("game modules found.\n");
				found = true;
				break;
			}
			pCheck = pCheck->GetNext();
		} while (pCheck);

		if (!found)
		{
			// check if timeout
			auto end = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
			if (elapsed >= 5)
			{
				printf("registration timeout. Library out of date?\n");
				return; 
			}
		}
	}


	// game modules are loading, time to load our stuff
	g_pInfinity->LoadPlugins();
}