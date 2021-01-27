proto native void PrintToDayZConsole(string value);
proto ScriptModule LoadSpecialModule(ScriptModule parent);


void TestFindPattern(ScriptModule parentModule)
{
	ScriptModule module = LoadSpecialModule(parentModule);
	if(module)
	{
		module.Call(NULL, "test_func", NULL);
	}
}