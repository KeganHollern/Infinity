#ifndef PATTERNS
#define PATTERNS
typedef HMODULE;

namespace Patterns {
	void* FindPatternMask(const char* pattern, const char* mask, HMODULE module, int offset);
	void* FindBinaryNinjaPattern(std::string pattern, HMODULE module, int offset);
}

#endif