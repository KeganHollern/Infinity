#pragma once
#ifndef PLUGINS
#define PLUGINS


#ifdef PLUGIN_EXPORT
#define _CLINKAGE __declspec(dllexport)
typedef void(__fastcall* ONPLUGINLOAD)();
#else
#define _CLINKAGE __declspec(dllimport)
#endif


namespace Infinity {
#ifdef PLUGIN_EXPORT
	namespace PluginSystem {
		void LoadPlugins(void* pThis);
		extern void* pScriptModule;
	}
#endif

	//debug logging functionality
	namespace Logging {
		_CLINKAGE void Print(const char* format, ...);
		_CLINKAGE void Error(const char* format, ...);
	}
	//generic utilities
	namespace Utils {
		_CLINKAGE void* FindPattern(const char* binary_ninja_pattern);
		_CLINKAGE void* FindPattern(const char* pattern, const char* mask);
		_CLINKAGE HRESULT HookFunction(void* pAddress, void* pHookFunction, void** pOriginal);
	}
	//enfusion specific functionality
	namespace Enfusion {
		//Infinity::Enfusion::GetProfilePath(buffer);
		_CLINKAGE bool GetProfilePath(char* pResult);
		_CLINKAGE void PrintToConsole(const char* format, ...);
		_CLINKAGE bool RegisterKeyPath(const char* directory, const char* key, bool allow_write = true);

		namespace Enscript {
			//Infinity::Enfusion::Enscript::RunFunction(obj, "func", NULL);
			_CLINKAGE bool RunFunction(void* object, const char* function, long long arg4);
			_CLINKAGE void* RegisterObject(const char* name);
			_CLINKAGE void RegisterFunctionForObject(void* pObject, const char* name, void* function, bool use_special_stack);
			_CLINKAGE void RegisterFunction(const char* name, void* function);
		}
	}
}

#endif