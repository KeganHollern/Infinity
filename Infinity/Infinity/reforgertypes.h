#pragma once
#include <stdint.h>

typedef uint64_t* (__fastcall* ADDFUNCTION)(void* pThis, const char* name, void* function, int32_t flag);
typedef uint64_t* (__fastcall* INITMODULES)(void* pThis, void* pUnknown);
typedef int64_t* (__fastcall* RUNFUNCTIONONNEWTHREAD)(void* pObject, int64_t* pResult, char* function_name, int64_t arg4);