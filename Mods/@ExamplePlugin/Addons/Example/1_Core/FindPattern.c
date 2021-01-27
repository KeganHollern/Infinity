proto native void PrintToDayZConsole(string value);
proto native ScriptModule LoadSpecialModule(ScriptModule parent);


void TestFindPattern(ScriptModule parentModule)
{
	if(!parentModule)
	{
		PrintToDayZConsole("Pattern Test Failed: Bad Parent Module!");
		return;
	}
	PrintToDayZConsole("Loading Special Module");
	ScriptModule module = LoadSpecialModule(parentModule);
	if(module)
	{
		if(FileExist("$sptmp:test.c"))
			PrintToDayZConsole("test.c exists!");
		
		PrintToDayZConsole("Script Module Loaded... Running...");
		module.Call(NULL, "test_func", NULL);
	}
}