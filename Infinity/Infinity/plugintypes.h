#pragma once

#include <Windows.h>
#include <stdint.h>

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
			typedef struct FunctionResult {
				PNativeArgument Result;
			} FunctionResult, * PFunctionResult;


			namespace Framework {

				// Created with ReClass.NET by KN4CK3R

				class ScriptContextTypes
				{
				public:
					class type* pType[305]; //0x0000
				private:
					char pad_0988[64]; //0x0988
				}; //Size: 0x09C8

				class ScriptContext
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					class type* pType; //0x0008
				private:
					char pad_0010[76]; //0x0010
				public:
					int32_t num_types; //0x005C
					class ScriptContextTypes* pTypes; //0x0060
				private:
					char pad_0068[56]; //0x0068
				}; //Size: 0x00A0

				class ScriptModule
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					class type* pType; //0x0008
				private:
					char pad_0010[8]; //0x0010
				public:
					int32_t ref_count; //0x0018
				private:
					char pad_001C[12]; //0x001C
				public:
					char* module_name; //0x0028
				private:
					char pad_0030[80]; //0x0030
				public:
					class ScriptContext* pContext; //0x0080
					class ScriptModule* pParent; //0x0088
				private:
					char pad_0090[64]; //0x0090
				}; //Size: 0x00D0

				class typename_variable
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					char* variable_name; //0x0008
				private:
					char pad_0010[16]; //0x0010
				public:
					class ScriptContext* pScriptContext; //0x0020
				private:
					char pad_0028[32]; //0x0028
				}; //Size: 0x0048

				class typename_variables
				{
				public:
					class typename_variable* pVariable; //0x0000
				private:
					char pad_0008[64]; //0x0008
				}; //Size: 0x0048

				class typename_function
				{
				private:
					char pad_0000[84]; //0x0000
				public:
					uint32_t some_value; //0x0054
					class ScriptContext* pContext; //0x0058
					char* name; //0x0060
				}; //Size: 0x0068

				class typename_functions
				{
				public:
					class typename_function* List[9]; //0x0000
				private:
					char pad_0048[128]; //0x0048
				}; //Size: 0x00C8

				class type
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					uint32_t flags; //0x0008
				private:
					char pad_000C[4]; //0x000C
				public:
					char* name; //0x0010
					class ScriptModule* pScriptModule; //0x0018
				private:
					char pad_0020[8]; //0x0020
				public:
					class type* pParent; //0x0028
				private:
					char pad_0030[8]; //0x0030
				public:
					class typename_variables* pVariables; //0x0038
				private:
					char pad_0040[4]; //0x0040
				public:
					uint32_t variableCount; //0x0044
					class typename_functions* pFunctions; //0x0048 used when running a func
				private:
					char pad_0050[144]; //0x0050
				public:
				}; //Size: 0x00E0

				class WeakPtrTracker
				{
				public:
					char pad_0000[24]; //0x0000
				}; //Size: 0x0018

				class ManagedScriptInstance
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					class type* pType; //0x0008
				private:
					char pad_0010[16]; //0x0010
				public:
					class WeakPtrTracker* pPtrTracker; //0x0020
				private:
					char pad_0028[24]; //0x0028
				}; //Size: 0x0040

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
					ListEntry List[127]; //0x0000
					char pad_07F0[1208]; //0x07F0
				}; //Size: 0x0CA8

				class FileHandler
				{
				public:
					char pad_0000[280]; //0x0000
					class FileSystemDefinitions* pDefinitions; //0x0118
					char pad_0120[672]; //0x0120
				}; //Size: 0x03C0

				class anyobject
				{
				public:
					char pad_0000[64]; //0x0000
				}; //Size: 0x0040



				class KeyValuePair
				{
				private:
					char pad_0000[4]; //0x0000
				public:
					bool hasValue; //0x0004
				private:
					char pad_0005[3]; //0x0005
				public:
					void* pKey; //0x0008
					void* pValue; //0x0010
				}; //Size: 0x0018

				class KeyValuePair_Map
				{
				public:
					KeyValuePair Pairs[255]; //0x0000
				}; //Size: 0x0120

				class Hashmap
				{
				public:
					char pad_0000[8]; //0x0000
				public:
					class type* pType; //0x0008
				private:
					char pad_0010[16]; //0x0010
				public:
					class WeakPtrTracker* pWeakPointerTracker; //0x0020
				private:
					char pad_0028[8]; //0x0028
				public:
					class KeyValuePair_Map* pMap; //0x0030
					int32_t Capacity; //0x0038
				private:
					char pad_003C[4]; //0x003C
				public:
					int32_t Size; //0x0040
				private:
					char pad_0048[0xC]; //0x0044


				private:
					int GetRawIndex(int32_t index)
					{
						//--- iterate over the entire capacity & look for element with our desired index
						int it = 0;
						if (index < Capacity && pMap)
						{
							for (int i = 0; i < Capacity; i++)
							{
								KeyValuePair pair = pMap->Pairs[i];
								if (pair.hasValue)
								{
									if (it == index)
										return i;

									it++;
								}
							}
						}
						return -1;
					}
				public:

					template<class TKey>
					TKey GetKey(int32_t index)
					{
						int idx = GetRawIndex(index);
						if (idx >= 0)
						{
							return (TKey)pMap->Pairs[idx].pKey;
						}
						return NULL;
					}
					template<class TValue>
					TValue ElementAt(int32_t index)
					{
						int idx = GetRawIndex(index);
						if (idx >= 0)
						{
							return (TValue)pMap->Pairs[idx].pValue;
						}
						return NULL;
					}
					template<class TKey, class TValue>
					TValue Get(TKey key)
					{
						if (!pMap)
							return NULL;
						//iterate over entire capacity to find our key match ( sadly we didn't implement efficient lookup :( )
						for (int i = 0; i < Capacity; i++)
						{
							if (pMap->Pairs[i].hasValue)
							{
								TKey srcKey = (TKey)pMap->Pairs[i].pKey;
								if (srcKey == key)
								{
									return (TValue)pMap->Pairs[i].pValue;
								}
							}
						}
						return NULL;
					}

				}; //Size: 0x0050



				class Array_Values
				{
				public:
					void* List[255]; //0x0000
				private:
					char pad_0010[64]; //0x0010
				}; //Size: 0x0050

				class Array
				{
				private:
					char pad_0000[8]; //0x0000
				public:
					class type* pType; //0x0008
				private:
					char pad_0010[16]; //0x0010
				public:
					class WeakPtrTracker* pWeakPtrTracker; //0x0020
					class Array_Values* pValues; //0x0028
					int32_t Capacity; //0x0030
					int32_t Size; //0x0034
				private:
					char pad_0038[24]; //0x0038


				public:
					template<class T>
					T GetValue(int32_t index)
					{
						if (pValues)
						{
							if (pValues->List)
							{
								return (T)pValues->List[index];
							}
						}
						return NULL;
					}
				}; //Size: 0x0050
			}
		}
	}
}