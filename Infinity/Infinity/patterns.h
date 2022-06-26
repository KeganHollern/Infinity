#pragma once

#include <string>
#include <Windows.h>

namespace Infinity {
	void* FindPattern(std::string pattern, HMODULE module, int offset);
}