#pragma once

#include "ScriptRegistrator.h"

typedef __int64 ScriptContext;
typedef __int64 ClassInstance;
typedef __int64 FunctionInstance;

typedef __int64(__fastcall* Enscript__Function)(__int64* a1, __int64* a2);
typedef ClassInstance*(__fastcall* Enscript__RegisterClass)(ScriptContext* scriptCtx, const char* className);
typedef FunctionInstance*(__fastcall* Enscript__RegisterClassStaticFunction)(ScriptContext* scriptCtx, ClassInstance* classInst, const char* functionName, Enscript__Function scriptFunction, unsigned int zero , char one);


extern Enscript__RegisterClass fRegisterClass;
extern Enscript__RegisterClassStaticFunction fRegisterClassStaticFunction;
extern ScriptRegistrator** g_pGlobalRegistrator;

extern const char** g_pStringModuleGame;


bool InitScriptEngine();