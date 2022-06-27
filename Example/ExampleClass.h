#pragma once

#include <InfinityPlugin.h>
#include <EnfusionTypes.hpp>


class ExampleClass : public Infinity::BaseScriptClass {
public:
	ExampleClass();
	void RegisterFunctions(Infinity::RegistrationFunction registerMethod) override;
private:
	static void TestFunction(Infinity::Enfusion::Enscript::FunctionContext* args, Infinity::Enfusion::Enscript::FunctionResult* result);
};