class DummyClass
{
	string inner_value = "value!";
	void Callback()
	{
		WriteToConsole("CALLBACK SUCCESS!");
	}
}
modded class MissionServer
{
	ref DummyClass dummy;
	override void OnInit()
	{
		WriteToConsole("PLUGIN TEST!");
		
		
		super.OnInit();
	}
}