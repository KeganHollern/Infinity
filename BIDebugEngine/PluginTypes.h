

#ifndef PLUGIN_TYPES
#define PLUGIN_TYPES

namespace Infinity {
	namespace Enfusion {
		namespace Enscript {
			//--- custom function context data structure
			typedef struct NativeArgument
			{
				void* Value;
			} NativeArgument, * PNativeArgument;
			typedef struct Arguments
			{
				PNativeArgument List[8];
			} Arguments, * PArguments;
			class FunctionContext
			{
				PArguments Arguments;
			public:
				PNativeArgument GetArgument(int idx)
				{
					if (!Arguments || !Arguments->List)
						return NULL;
					return Arguments->List[idx];
				}
			};

			namespace Framework {

				// Created with ReClass.NET by KN4CK3R (see reclass file in repo)

				class ScriptContextTypes
				{
				public:
					class type* pType[305]; //0x0000
					char pad_0988[64]; //0x0988
				}; //Size: 0x09C8

				class ScriptContext
				{
				public:
					char pad_0000[8]; //0x0000
					class type* pType; //0x0008
					char pad_0010[76]; //0x0010
					int32_t num_types; //0x005C
					class ScriptContextTypes* pTypes; //0x0060
					char pad_0068[56]; //0x0068
				}; //Size: 0x00A0

				class ScriptModule
				{
				public:
					char pad_0000[8]; //0x0000
					class type* pType; //0x0008
					char pad_0010[8]; //0x0010
					int32_t ref_count; //0x0018
					char pad_001C[12]; //0x001C
					char* module_name; //0x0028
					char pad_0030[80]; //0x0030
					class ScriptContext* pContext; //0x0080
					class ScriptModule* pParent; //0x0088
					char pad_0090[64]; //0x0090
				}; //Size: 0x00D0

				class typename_variable
				{
				public:
					char pad_0000[8]; //0x0000
					char* variable_name; //0x0008
					char pad_0010[16]; //0x0010
					class ScriptContext* pScriptContext; //0x0020
					char pad_0028[32]; //0x0028
				}; //Size: 0x0048

				class typename_variables
				{
				public:
					class typename_variable* pVariable; //0x0000
					char pad_0008[64]; //0x0008
				}; //Size: 0x0048

				class typename_function
				{
				public:
					char pad_0000[84]; //0x0000
					uint32_t some_value; //0x0054
					class ScriptContext* pContext; //0x0058
					char* name; //0x0060
				}; //Size: 0x0068

				class typename_functions
				{
				public:
					class typename_function* List[9]; //0x0000
					char pad_0048[128]; //0x0048
				}; //Size: 0x00C8

				class type
				{
				public:
					char pad_0000[8]; //0x0000
					uint32_t flags; //0x0008
					char pad_000C[4]; //0x000C
					char* name; //0x0010
					class ScriptModule* pScriptModule; //0x0018
					char pad_0020[8]; //0x0020
					class type* pParent; //0x0028
					char pad_0030[8]; //0x0030
					class typename_variables* pVariables; //0x0038
					char pad_0040[4]; //0x0040
					uint32_t variableCount; //0x0044
					class typename_functions* pFunctions; //0x0048 used when running a func
					char pad_0050[144]; //0x0050
				}; //Size: 0x00E0

				class WeakPtrTracker
				{
				public:
					char pad_0000[24]; //0x0000
				}; //Size: 0x0018

				class ManagedScriptInstance
				{
				public:
					char pad_0000[8]; //0x0000
					class type* pType; //0x0008
					char pad_0010[16]; //0x0010
					class WeakPtrTracker* pPtrTracker; //0x0020
					char pad_0028[24]; //0x0028
				}; //Size: 0x0040

			}
		}
	
		class FileSystemDef
		{
		public:
			char pad_0000[24]; //0x0000
			char* path; //0x0018
			char* key; //0x0020
			uint32_t type_flag; //0x0028
			char pad_002C[12]; //0x002C
		}; //Size: 0x0038

		class ListEntry
		{
		public:
			char pad_0000[8]; //0x0000
			class FileSystemDef* pDefinition; //0x0008
		}; //Size: 0x0010

		class FileSystemDefinitions
		{
		public:
			ListEntry List[126]; //0x0000
			char pad_07E0[1208]; //0x07E0
		}; //Size: 0x0C98

		class FileHandler
		{
		public:
			char pad_0000[280]; //0x0000
			class FileSystemDefinitions* pDefinitions; //0x0118
			char pad_0120[672]; //0x0120
		}; //Size: 0x03C0
	}
}

#endif