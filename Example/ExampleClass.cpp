
#include <InfinityPlugin.h>
#include <EnfusionTypes.hpp>


#include "ExampleClass.h"


using namespace Infinity;
using namespace Infinity::Logging;
using namespace Infinity::Enfusion::Enscript;
using namespace Infinity::Enfusion::Enscript::Framework;


/*
sealed class ExampleClass {
	static proto void TestFunction(string value);
}

*/

ExampleClass::ExampleClass() : BaseScriptClass("ExampleClass") {}
void ExampleClass::RegisterFunctions(Infinity::RegistrationFunction registerMethod) {
	registerMethod("TestFunction", &ExampleClass::TestFunction);
};
void ExampleClass::TestFunction(Infinity::Enfusion::Enscript::FunctionContext* args, Infinity::Enfusion::Enscript::FunctionResult* result)
{
	const char* input = (const char*)args->GetArgument(0)->Value; // arg0 is a string

	Println("Testing Function: %s", input);
}