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
		}
		bool HookInit();
		bool GetProfilePath(char* pResult);
		void* GetFileHandler();
		void RegisterPathKey(void* pFileHandler, const char* path, const char* key, bool allow_write);
		bool IsValidForMode(char* filepath, int32_t mode);
		int64_t CanAccessFile(void* pHandle, LPCSTR filepath);
	}
}

#endif