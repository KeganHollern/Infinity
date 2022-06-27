#pragma once

#include <functional>

#ifdef INFINITYHOST_EXPORTS
#define _CLINKAGE __declspec(dllexport)
#else
#define _CLINKAGE __declspec(dllimport)
#endif

namespace Infinity {
#ifdef INFINITYHOST_EXPORTS
	typedef void(__fastcall* ONPLUGINLOAD)();
	void LoadPlugins(); // calls OnPluginLoad() export so Register can be called
#endif
	// -------------------------------------------------------------------------
	// script class registration
	typedef std::function<bool(const char*, void*)> RegistrationFunction;
	class _CLINKAGE BaseScriptClass {
	public:
		BaseScriptClass(const char* name);
		const char* GetName();
		// override this function to register your script routines to this class.
		virtual void RegisterFunctions(RegistrationFunction registerMethod);
	protected:
		const char* className;
	};
	// Call this routine during OnPluginLoad to register custom script classes
	_CLINKAGE void RegisterScriptClass(BaseScriptClass* pScriptClass); // register a script class 

	// --------------------------------------------------------------------------
	// useful methods exposed for plugins
	namespace Logging {
		_CLINKAGE void Println(const char* format, ...);
		_CLINKAGE void Errorln(const char* format, ...);
		_CLINKAGE void Warnln(const char* format, ...);
		_CLINKAGE void Debugln(const char* format, ...);
	}
	namespace Utils {
		//_CLINKAGE void* FindPattern(const char* binary_ninja_pattern);
	}
	namespace Enfusion {
		//_CLINKAGE bool RegisterKeyPath(const char* directory, const char* key, bool allow_write = true); // register path to $key: for file access
	}
}


