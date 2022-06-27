#pragma once
#include <Windows.h>


#ifdef INFINITYHOST_EXPORTS
#define _CLINKAGE __declspec(dllexport)
typedef void(__fastcall* ONPLUGINLOAD)();
#else
#define _CLINKAGE __declspec(dllimport)
#endif

namespace Infinity {
#ifdef INFINITYHOST_EXPORTS
	void LoadPlugins(void* pScriptContext);
#endif

	//debug logging functionality
	namespace Logging {
		_CLINKAGE void Println(const char* format, ...);
		_CLINKAGE void Errorln (const char* format, ...);
		_CLINKAGE void Warnln(const char* format, ...);
		_CLINKAGE void Debugln(const char* format, ...);
	}
	namespace Utils {
		_CLINKAGE void* FindPattern(const char* binary_ninja_pattern);
	}
	namespace Enfusion {
		_CLINKAGE const char* GetGame(); // get game name
		//_CLINKAGE bool RegisterKeyPath(const char* directory, const char* key, bool allow_write = true); // register path to $key: for file access
		//_CLINKAGE void* MemAlloc(SIZE_T size); // call enf_memory allocator
		namespace Enscript {
			_CLINKAGE void* RegisterFunction(const char* name, void* function);
			_CLINKAGE bool RunFunction(void* object, const char* function, long long arg4);
		}
	}
}