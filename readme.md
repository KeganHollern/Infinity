

<img src="https://kegan-screenshot.ewr1.vultrobjects.com/2021-01-24/22-05-39/infinity2.png" alt="img" style="zoom: 33%;" /> Enfusion Infinity 
===============

[TOC]

## What is it?

Infinity is a C/C++ plugin and extension framework for the Enfusion engine. The goal of Infinity is to empower modders with the ability to extend Enscript with custom native functionality.  

Simply put, Infinity provides modders with the framework to implement their own `proto` functionality into the engine. Natively,`proto` methods call underlying C++ functionality, which modders can not access on their own. 

This is achieved with a plugin system implemented by the Infinity library. Modders develop their own drag-and-drop plugins.

## Plugins

Plugins are the main feature of Infinity. With plugins, you can load your own native assembly into the DayZ Server process. This assembly can register it's own `proto` functions with the Enfusion scripting engine. 

Plugins go into the `Plugins` folder in the DayZ Server. These libraries are automatically loaded on server start. 

### Technical Details

Plugins are loaded during the Module Init phase. During this time, the game registers it's own proto natives. Plugins are loaded prior to the game loading it's own proto natives, and therefore *should* be able to overwrite them if necessary (though untested). 

In order for a plugin to start, it must export the `OnPluginLoad` method. Here is a sample:

```c++
void __declspec(dllexport) OnPluginLoad()
{
	Infinity::Logging::Print("Sample Plugin Loaded!");
}
```

#### More Code Samples

Custom `proto native` functionality can be implemented using the `RegisterFunction` method. Here is a sample:

```c++
// In Enscript: proto native bool ExampleFunction(string test_str); //returns true if test_str contains "test"
bool ExampleFunction(char* input)
{
    if(strstr(input,"test"))
        return true;
    return false;
}

void __declspec(dllexport) OnPluginLoad()
{
    Infinity::Enfusion::Enscript::RegisterFunction("ExampleFunction", &ExampleFunction);
	Infinity::Logging::Print("Function Registered!");
}
```

Custom path keys can be added using the `RegisterKeyPath` method. Here is a sample:

```c++
void __declspec(dllexport) OnPluginLoad()
{
    //register $testdir: | with this we can read files in that directory with "$testdir:filename.txt"
    //true is included to enable write to this directory as well
    if (Infinity::Enfusion::RegisterKeyPath("C:\\Users\\kegan\\Documents\\Test", "testdir", true))
		Infinity::Logging::Print("Registered Key Path!");
	else
		Infinity::Logging::Error("Failed to register key path!");
}
```

Plugins can print to the GUI console with the `PrintToConsole` method. Here is a sample:

```c++
void __declspec(dllexport) OnPluginLoad()
{
    Infinity::Enfusion::PrintToConsole("Loaded Test");
}
```

### Examples

Included in this repository are several example plugins. These can be used as code samples, or even full on plugins for your server. They are not shipped in any RC & will need to be recompiled manually.

Here are some short descriptions of the examples:

#### PipePluginTest

This plugin enables named pipe read/write functionality for enscript.

#### ExamplePlugin

This plugin is a simple function registration example. It is being actively developed to include custom object construction.

#### ObjectTestPlugin

This was a more advanced example of function registration. Included are samples of non-native `proto` functions and the use of the `FindPattern` functionality provided for plugins.

## Extensions

Infinity has it's own implementation of Arma 3's [callExtension](https://community.bistudio.com/wiki/callExtension). This recreates the exact specifications for RVExtension and others in DayZ. The purpose is to enable integrations of Arma 3 extensions such as [extDB](https://github.com/SteezCram/extDB3). The use of extensions requires the `RVExt.pbo` addon be included on the server. This pbo is shipped with the release client & I am authorizing anyone to upload it to workshop with their own mod. 

### Limitations

The limitations of callExtension have been kept in order to accurately reflect the functionality in Arma 3. Due to this, the maximum output size is 10240 bytes. 

### Examples

Provided in the Extensions directory is the HTTP-GET Example extension. This is an Arma 3 extension that enables GET requests. This extension showcases the implementation of callExtension, and the support for .NET extensions.

## Installation

Infinity is a server-only mod. This means you can only add plugins, and therefore implement `proto` methods, on the server. By that, install takes place on the server.

### Server Install

The following steps must be complete prior to installing Infinity

1. Install your DayZ Server 
2. Run your DayZ Server once to create the profile.

To install Infinity runtime, follow these steps:

1. Download the latest runtime RC. 
2. Create a `Plugins` folder in your *server root* directory.
3. Extract the runtime & place `BIDebugEngine.dll` in the *server root*.

If you wish to enable extensions:

1. Extract the runtime & add the `RVExt.pbo` file to your modpack.

Your server now has Infinity installed. Launch with `-rvdbg` to see if the debug console opens up!

### Devkit Install

To install the devkit, follow these steps:

1. Download the latest devkit RC.
2. Extract the devkit to a nice safe location on your PC

To use the devkit with Visual Studio 2019 follow these steps:

1. Create a new `Dynamic-Link Library (DLL)` project.
2. Right click your new project & select `Properties`
3. Under `Properties->VC++ Directories` edit `Include Directories`
4. Add the `devkit/include` path to the include directories.
5. Under `Properties->Linker->Input` edit `Additional Dependencies` 
6. Add the `devkit/lib/BIDebugEngine.lib` path to the addition dependencies.

With these steps, you should be able to begin creating a plugin.

## Feature List

- [x] Load Library on Server Start using BIDebugEngine.dll
- [x] Debug console with `-rvdbg` launch parameter
- [x] Custom global `proto native` definitions
- [x] Print messages directly to the GUI console
- [x] [callExtension](https://community.bistudio.com/wiki/callExtension) implementation
- [x] Plugin loading from `./plugins` directory
- [x] Plugins can register global `proto native` definitions
- [x] Plugins can register custom `class` definitions
- [x] Plugins can register class `proto native` definitions (static only)
- [x] Plugins can register `proto` definitions (global and class)
- [x] Framework for handling non-native `proto` definitions easily
- [x] Plugins can print to debug console & GUI console
- [x] Plugins can register custom path keys. Ex: `$customkey:test.c` could map to `C:\test.c`
- [x] Custom path keys can be written to (if enabled)
- [x] Plugins can get the profile path
- [x] Enable FindPattern for plugins, so they can add more advanced functionality.
- [x] Framework for easily handling Managed classes from Enscript
- [ ] Plugins can construct custom `class` definitions natively
- [ ] Plugins can register non-static class `proto native` definitions
- [ ] Framework for easily handling custom registered `class` definitions
- [ ] Add `-nobe` launch parameter to disable battleye
- [ ] Add `-globalwrite` launch paramter to enable write to all file paths
- [ ] Plugins can enable write to custom path keys post-creation
- [ ] .NET plugins

And more will be added!

## Final Notes & License

This code was originally based on: https://github.com/gallexme/EnfScriptHook-Extender 
No code from EnfScriptHook-Extender remains in the current version of the project.

Infinity is licensed under the MIT license. You can find the full license in the LICENSE file.

