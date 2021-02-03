
modded class MissionServer
{
	override void OnInit()
	{
		Print("RUNNING TEST PLUGIN!");
		
		TestGlobalProtos();
		TestClassProtos();
		TestCallbacks();
		TestFindPattern(GetGame().GetMission().MissionScript);
		TestHookFunction();
		TestSetValue();
		TestArrayUsage();
		super.OnInit();
	}
}