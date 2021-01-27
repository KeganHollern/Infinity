#pragma once


#ifndef DAYZ_TYPES
#define DAYZ_TYPES

typedef struct GETTYPE_RESULT {
	uint64_t* pType;
	uint64_t unk; //i think this can be a uint32_t
} GETTYPE_RESULT;

typedef uint64_t* (__fastcall* INITMODULES)(void* pThis);
typedef uint64_t* (__fastcall* ADDFUNCTION)(void* pThis, const char* name, void* function, int32_t flag);
typedef GETTYPE_RESULT* (__fastcall* GETTYPENAME)(void* pThis, void* pResult, const char* name, char mode);
typedef uint64_t* (__fastcall* ADDCLASSFUNCTION)(void* pThis, void* pParentType, const char* name, void* function, int32_t flag, char flag2);
//verify this
typedef int64_t (__fastcall* CONSOLEPRINT)(const char* arg1, va_list formatable_params);

typedef int64_t* (__fastcall* RUNFUNCTIONONNEWTHREAD)(void* pObject, int64_t* pResult, char* function_name, int64_t arg4);
typedef uint64_t (__fastcall* GETPROFILEPATH)(char* pResult);
typedef bool (__fastcall* REGISTERPATHKEY)(void* pFileHandler, char* path, int32_t flag, char* key, int32_t flag1, int64_t flag2);
typedef bool (__fastcall* ISVALIDFORMODE)(char* filepath, int32_t mode);
typedef int64_t(__fastcall* CANACCESSFILE)(void* pFileHandler, LPCSTR filepath);
typedef int64_t(__fastcall* ALLOCENFMEMORY)(SIZE_T arg1);
typedef void* (__fastcall* SETSTRINGARGUMENTVALUE)(char* new_value, void* pArgInfo, char** pArgument, bool unk_bool);
typedef bool (__fastcall* ISARGUMENTNULL)(void** pArgument);
typedef void* (__fastcall* GETARGUMENTINFO)(void* pFunctionContext, int32_t arg_index);

#endif