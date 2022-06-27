#pragma once
#include <iostream>
#include <cstdarg>
#include <Windows.h>


inline bool IsPartOf(const char* a, char* b) {
	if (std::strstr(b, a) != NULL) {    //Strstr says does b contain a
		return true;
	}
	return false;
}
inline bool IsDebug()
{
#ifdef _DEBUG
	return true;
#else
	char* cmd = GetCommandLineA();
	return IsPartOf(" -debug ", cmd); //looking for -debug in command line params
#endif
}

inline int Println(const char* format, ...)
{
	printf("INFINITY     : ");
	va_list vl;
	va_start(vl, format);
	auto ret = vprintf(format, vl);
	va_end(vl);
	printf("\n");
	return ret;
}
inline int Debugln(const char* format, ...)
{
	if (!IsDebug()) return 0;

	printf("INFINITY  (D): ");
	va_list vl;
	va_start(vl, format);
	auto ret = vprintf(format, vl);
	va_end(vl);
	printf("\n");
	return ret;
}
inline int Errorln(const char* format, ...)
{
	printf("INFINITY  (E): ");
	va_list vl;
	va_start(vl, format);
	auto ret = vprintf(format, vl);
	va_end(vl);
	printf("\n");
	return ret;
}
inline int Warnln(const char* format, ...)
{
	printf("INFINITY  (W): ");
	va_list vl;
	va_start(vl, format);
	auto ret = vprintf(format, vl);
	va_end(vl);
	printf("\n");
	return ret;
}
