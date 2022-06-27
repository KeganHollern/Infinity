#pragma once

#include <string>


class ScriptRegistrator {
public:
	// constructor
	ScriptRegistrator();
	// virtual table

	virtual ~ScriptRegistrator();// 0
	virtual __int64 unk0() { printf("unk0");  return false; } // 1
	virtual __int64 Register(__int64 a2) { printf("register"); return true; } // 2
	virtual __int64 unk1() { printf("unk1"); return true; } // 3 (must be true)
	virtual __int64 unk2() { printf("unk2"); return false; }
	virtual __int64 unk3() { printf("unk3"); return true; }
	virtual __int64 unk4() { printf("unk4"); return false; }
	virtual __int64 unk5() { printf("unk5"); return false; }
	virtual __int64 unk6() { printf("unk6"); return false; }

	ScriptRegistrator* GetLast();
	void Insert(ScriptRegistrator* registrator);
	ScriptRegistrator* GetNext();
	const char* GetName();
	bool HasChild(ScriptRegistrator* child);
protected:
	const char* pModuleName; // 0x8
	ScriptRegistrator* pNext; // 0x10
	void* pClass; // 0x18
};

class BaseScriptRegistrator : public ScriptRegistrator {
public:
	BaseScriptRegistrator(std::string name);
	virtual ~BaseScriptRegistrator() override;

	__int64 Register(__int64 a2) override;
protected:
	std::string className;
};