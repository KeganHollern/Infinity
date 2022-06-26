#pragma once
#include <Windows.h>
#include <string>
#include <MinHook.h>

#include "console.hpp"


namespace Infinity {
	class Engine {
	public:
		// game dependent routines
		virtual const char* Game() { return "No Game"; };
		virtual void Init() { Errorln("no engine init defined."); }; // init hooks
		int ApplyHook(void* address, void* method, void** original); // apply minhook hook

		// all enfusion functionality we want to expose
		virtual void* RegisterGlobal(void* pScriptContext, const char* name, void* function) { Errorln("no engine registerglobal defined."); return nullptr; };
		virtual bool RunFunction(void* object, const char* function, long long arg4) { Errorln("no engine runfunction defined."); return false; };

		//TODO: implement those below
		
		//virtual void* MemAlloc(SIZE_T size) { Errorln("no engine memalloc defined.");  return nullptr; };
		//virtual bool RegisterPathKey(const char* path, const char* key, bool allow_write) { Errorln("no engine registerpathkey defined."); return false; }

	protected:
		void* FindFunction(const char* name, std::string pattern, int offset = 0); // find a function by pattern

	};
}