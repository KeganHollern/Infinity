#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "../BIDebugEngine/Plugins.h"
#include "../BIDebugEngine/PluginTypes.h"

const char* pipe_name = "\\\\.\\pipe\\testpipe";
HANDLE hPipe;

int OpenPipe(char* name)
{
	return 0;
}
int ReadPipe(char* name, char* buffer, int buffer_len)
{
	return 0;
}
int WritePipe(char* name, char* data)
{
	return 0;
}

void __declspec(dllexport) OnPluginLoad()
{
	Infinity::Logging::Print("Loading Pipe Test...");

	//example pipe for testing
	hPipe = CreateNamedPipeA(pipe_name, PIPE_ACCESS_DUPLEX, PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);

	
	Infinity::Logging::Print("Finished Initializing Pipe Test!");
}