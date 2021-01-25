#ifndef DAYZ_SCRIPTS
#define DAYZ_SCRITPS

namespace DayZ {
	namespace Scripts 
	{
		namespace Internal {
			extern INITMODULES dayzInitModules;
			extern ADDFUNCTION dayzRegisterFunction;
			extern GETTYPENAME dayzGetTypeFunction;
			extern ADDCLASSFUNCTION dayzRegisterClassFunction;
			extern RUNFUNCTIONONNEWTHREAD dayzRunFunction;
		}

		uint64_t* RegisterObject(void* pThis, const char* name);
		uint64_t* FindObject(void* pThis, const char* name);
		uint64_t* Register(void* pThis, void* pParent, const char* name, void* function, bool use_special_stack);
		uint64_t* RegisterGlobal(void* pThis, const char* name, void* function);
		uint64_t* InitModules(void* pThis);

		bool RunFunction(void* pObject, const char* function, int64_t arg4 = NULL);
	}
}
#endif