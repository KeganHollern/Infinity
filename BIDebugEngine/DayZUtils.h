#ifndef DAYZ_UTILS
#define DAYZ_UTILS

namespace DayZ {
	namespace Utils
	{
		namespace Internal {
			extern CONSOLEPRINT dayzConsolePrint;
		}
		void PrintToConsole(const char* format, ...);
	}
}

#endif