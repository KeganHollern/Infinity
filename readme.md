

Enfusion Infinity 
===============

## What is it?

Infinity is a C/C++ plugin and extension framework for the Enfusion engine. The goal of Infinity is to empower modders with the ability to extend Enscript with custom native functionality.  

Simply put, Infinity provides modders with the framework to implement their own `proto` functionality into the engine. Natively,`proto` methods call underlying C++ functionality, which modders can not access on their own. 

This is achieved with a plugin system implemented by the Infinity library. Modders develop their own drag-and-drop plugins.

## Plugins

Plugins are the main feature of Infinity. With plugins, you can load your own native assembly into the Enfusion Server process. This assembly can register it's own `proto` functions with the Enfusion scripting engine. 

Plugins go into the `Plugins` folder in the DayZ Server. These libraries are automatically loaded on server start. 

### Technical Details

Plugins are loaded during the Module Init phase. During this time, the game registers it's own script classes. Plugins are loaded after the game loads it's own functions.

In order for a plugin to start, it must export the `OnPluginLoad` method. Here is a sample:

```c++
#include <InfinityPlugin.h>

void __declspec(dllexport) OnPluginLoad()
{
	Infinity::Logging::Print("Sample Plugin Loaded!");
}
```

#### More Code Samples

Custom `proto` functionality is implemented using the `BaseScriptClass` and `RegisterScriptClass` tooling.

```c++
#include <InfinityPlugin.h>
#include <EnfusionTypes.hpp>

using namespace Infinity;
using namespace Infinity::Logging;

// extend from Infinity::BaseScriptClass
class ExampleClass : public BaseScriptClass {
public:
	ExampleClass() : BaseScriptClass("ExampleClass") {} // the string passed here is the class name in enscript
	void RegisterFunctions(RegistrationFunction registerMethod) override {
        registerMethod("TestFunction", &ExampleClass::TestFunction); // the string passed here is the function name in enscript
    }
private:
	static void TestFunction(Enfusion::Enscript::FunctionContext* args, Enfusion::Enscript::FunctionResult* result) {
        const char* input = (const char*)args->GetArgument(0)->Value; // arg0 is a string
	    Println("Testing Function: %s", input); 
    }
};

void __declspec(dllexport) OnPluginLoad()
{
	RegisterScriptClass(new ExampleClass()); // register our example class
	Println("Example plugin loaded.");
}
```

### Examples

Included in this repository is an example plugin project.

## Installation

Infinity is a workbench and server-only mod. This means you can only add plugins, and therefore implement `proto` methods, on the server.

### Host Install

The following steps must be complete prior to installing Infinity

1. Install your Enfusion Server 
2. Run your Enfusion Server once to create the profile.

To install Infinity runtime, follow these steps:

1. Download the latest runtime RC. 
2. Create a `Plugins` folder in your *server root* directory.
3. Extract the runtime & place `Secur32.dll` in the *server root*.

## Feature List

- [x] Load Library on Engine Start using Secur32.dll
- [x] Pretty print to console
- [x] Plugin loading from `./plugins` directory
- [x] Plugins can register custom `class` definitions
- [x] Plugins can register class `proto` definitions (static only)
- [ ] Plugins can register class `proto native` definitions (static only)
- [ ] Plugins can register custom path keys. Ex: `$customkey:test.c` could map to `C:\test.c`
- [ ] Custom path keys can be written to (if enabled)
- [ ] Enable FindPattern for plugins, so they can add more advanced functionality.
- [ ] Enable Hooking for plugins, so they can add more advanced functionality.
- [ ] Plugins can get the profile path
- [ ] [callExtension](https://community.bistudio.com/wiki/callExtension) implementation
- [x] Framework for handling non-native `proto` definitions easily
- [x] Framework for easily handling Managed classes from Enscript
- [ ] Framework for easily handling custom registered `class` definitions
- [ ] Add `-globalwrite` launch paramter to enable write to all file paths
- [ ] Plugins can enable write to custom path keys post-creation
- [ ] .NET plugins
- [ ] Plugins can construct custom `class` definitions natively
- [ ] Plugins can register non-static class `proto native` definitions

And more will be added!

## Final Notes & License

This code was originally based on: https://github.com/gallexme/EnfScriptHook-Extender and https://github.com/intercept/interceptAR
No code from EnfScriptHook-Extender or interceptAR remains in the current version of the project.

Infinity is licensed under the MIT license. You can find the full license in the LICENSE file.

