#ifndef RVEXTENSION
#define RVEXTENSION

#define MAX_BUFFER_SIZE 10240

//custom dzextension format
typedef char* (__stdcall* DZExtensionFunction)(char* function, char* arguments); 

//legacy rvextension methods
typedef void(__stdcall* RVExtensionVersionFunction)(char* output, int outputSize);
typedef void(__stdcall* RVExtensionFunction)(char* output, int outputSize, const char* function);
typedef int(__stdcall* RVExtensionArgsFunction)(char* output, int outputSize, const char* function, const char** args, int argsCnt);

typedef HMODULE;

namespace RVExt {
	HMODULE GetExtension(const char* library);
	char* callExt_DZ(char* library, char* function, char* argument);
	char* callExt_RVArgs(char* library, char* function, const char*** args, int argsCount);
	char* callExt_RV(char* library, char* function);
	char* callExt_RVVer(char* library);

}
#endif