// InfinityServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>

#include <filesystem>
#include <iostream>
#include <consoleapi2.h>
#include <conio.h>
#include <string>
#include <map>
#include <vector>
#include <winternl.h>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    SetConsoleTitle(L"Infinity Server Starter");

    std::vector<std::string> exact_args;
    std::map<std::string, std::string> arguments;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg(argv[i]);
            exact_args.push_back("\"" + arg + "\""); //keep a clone of all arguments
            if (arg.find("-", 0) == 0) //must start with -
            {
                size_t index = arg.find("=", 1);
                std::string value = "<no:value>";
                std::string key = arg.substr(1);
                if (index != std::string::npos)
                {
                    value = arg.substr(index + 1);
                    key = arg.substr(1, index-1);
                }
                arguments.insert(std::pair<std::string, std::string>(key, value));
                std::cout << "\tArg '" << key << "'='" << value << "'" << std::endl;
            }
        }
    }



    if (arguments["help"] != "")
    {
        std::cout << "Infinity Injection Server" << std::endl \
            << "+++ HELP! +++" << std::endl \
            << "" << std::endl \
            << "Arguments: " << std::endl \
            << "\t-isvr=DayZServer_x64.exe" << std::endl \
            << "\t\tisvr specifies the dayz server executable. By default this is DayZServer_x64.exe" << std::endl \
            << "\t-ilib=BIDebugEngine.dll" << std::endl \
            << "\t\tilib specifies the library to inject into dayz. By default this is BIDebugEngine.dll" << std::endl \
            << "\t-iblk" << std::endl \
            << "\t\tiblk will prevent InfinityServer from exiting until DayZServer does. Useful for restart scripts." << std::endl \
            << "Note: all excess arguments are passed into the DayZ Server." << std::endl \
            << "" << std::endl \
            << "How to use:" << std::endl \
            << "\tPlace this executable in your DayZ Server folder." << std::endl \
            << "\tReplace DayZServer_x64.exe with InfinityServer.exe in your startup script!" << std::endl \
            << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        getchar();
        return 0;
    }

    bool blocking = arguments["iblk"] != "";

    if (arguments["isvr"] == "")
        arguments["isvr"] = "DayZServer_x64.exe";
    if(arguments["ilib"] == "")
        arguments["ilib"] = "BIDebugEngine.dll";


    if (!fs::exists(arguments["isvr"]))
    {
        std::cout << "Critical Error: " << arguments["server"] << " not found!" << std::endl \
            << "Use -help for help!" << std::endl;
        return 1;
    }
    if (!fs::exists(arguments["ilib"]))
    {
        std::cout << "Critical Error: " << arguments["library"] << " not found!" << std::endl \
            << "Use -help for help!" << std::endl;
        return 1;
    }
    fs::path server_full_path = fs::canonical(fs::path(arguments["isvr"]));
    fs::path library_full_path = fs::canonical(fs::path(arguments["ilib"]));



    std::string cmdline = "";
    for (std::string arg : exact_args)
        cmdline += arg + " ";
    

    //1. start our dayz server process with our arguments we want
    STARTUPINFOA info;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&info, sizeof(info));
    info.cb = sizeof(info);
    ZeroMemory(&processInfo, sizeof(processInfo));

    std::cout << "Starting Infinity DayZ!" << std::endl;
    if (CreateProcessA(server_full_path.string().c_str(), (char*)cmdline.c_str(), NULL, NULL, TRUE, DETACHED_PROCESS, NULL, NULL, &info, &processInfo))
    {
        //2.  elevate process handle if necessary
        //processInfo.hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.dwProcessId);
        std::string lib_path = library_full_path.string().c_str();
        //2. allocate space in DayZServer for our library string
        void* pRemoteAddr = VirtualAllocEx(processInfo.hProcess, NULL, lib_path.length() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (!pRemoteAddr)
        {
            std::cout << "Failed VirtualAllocEx - " << std::hex << GetLastError() << std::endl;
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
            return 1;
        }
        //3. write library string to DayZServer
        if (!WriteProcessMemory(processInfo.hProcess, pRemoteAddr, lib_path.c_str(), lib_path.length(), NULL))
        {
            std::cout << "Failed WriteProcessMemory - " << std::hex << GetLastError() << std::endl;
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
            return 1;
        }
        //3. call loadlibrary w/ our library path string as an argument
        void* pLoadLibrary = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA"); //we use loadlibraryA because our string is *not* wide (otherwise we'd use loadlibraryw)
        HANDLE hThread = CreateRemoteThread(processInfo.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pLoadLibrary, pRemoteAddr, NULL, NULL);
        if (!hThread)
        {
            std::cout << "Failed CreateRemoteThread - " << std::hex << GetLastError() << std::endl;
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
            return 1;
        }

        if (blocking)
        {
            std::cout << "Infinity Loaded! Waiting for DayZ to Exit..." << std::endl;
            WaitForSingleObject(processInfo.hProcess, INFINITE);
        }

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        CloseHandle(hThread);
    }
    else
    {
        std::cout << "Failed to create process - " << std::hex << GetLastError() << std::endl;
        std::cout << server_full_path.string() << " | " << cmdline << std::endl;
        return 1;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
