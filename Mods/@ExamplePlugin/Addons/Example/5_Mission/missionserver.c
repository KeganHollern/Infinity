
modded class MissionServer
{
	override void OnInit()
	{
		Print("RUNNING TEST PLUGIN!");
		
		TestGlobalProtos();
		TestClassProtos();
		TestCallbacks();
		TestFindPattern();
		TestHookFunction();
		TestSetValue();
		
		super.OnInit();
	}
}