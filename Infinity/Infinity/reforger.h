#pragma once

#include "engine.h"
#include "reforgertypes.h"



namespace Infinity {
	class Reforger : public Engine {
	public:
		const char* Game();
		void Init();
		void* RegisterGlobal(void* pScriptContext, const char* name, void* function);
		bool RunFunction(void* object, const char* function, long long arg4);

		INITMODULES oInitModules;
	protected:
		ADDFUNCTION fRegisterGlobal;
		RUNFUNCTIONONNEWTHREAD fRunFunction;
	};

	uint64_t* HK_Reforger_InitModules(void* pScriptContext, void* pUnknown);
}