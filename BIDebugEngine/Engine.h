#ifndef DAYZ_ENGINE
#define DAYZ_ENGINE


namespace DayZ {
	namespace Engine
	{
		namespace Internal
		{
			extern GETPROFILEPATH dayzGetProfilePath;
			extern void** dayzFileHandlerPtr;
			extern REGISTERPATHKEY dayzRegisterPathKey;
			extern ISVALIDFORMODE dayzIsValidForMode;
			extern CANACCESSFILE dayzCanAccessFile;
			extern std::vector<std::string> allow_write_path_keys;
			extern ALLOCENFMEMORY dayzAllocEnfMemory;
			extern SETSTRINGARGUMENTVALUE dayzSetStringArgumentValue;
			extern ISARGUMENTNULL dayzIsArgumentNull;
			extern GETARGUMENTINFO dayzGetArgumentInfo;
		}
		bool HookInit();
		bool GetProfilePath(char* pResult);
		void* GetFileHandler();
		void RegisterPathKey(void* pFileHandler, const char* path, const char* key, bool allow_write);
		bool IsValidForMode(char* filepath, int32_t mode);
		int ApplyHook(void* address, void* method, void** original);
		int64_t CanAccessFile(void* pHandle, LPCSTR filepath);
		void* MemAlloc(SIZE_T size);
		bool IsArgumentNull(void** pArgument);
		void SetStringArgumentValue(char* new_value, void* pArgumentInfo, char** pArgument, bool unk_bool);
		void* GetArgumentInfo(void* pContext, int iArgIndex);
	}
}

#endif