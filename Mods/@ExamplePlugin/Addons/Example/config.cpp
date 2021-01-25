class CfgMods
{
	class ExamplePlugin
	{
		dir = "@ExamplePlugin";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ExamplePlugin";
		author = "Lystic";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] =
				{
					"Example/1_Core"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"Example/5_Mission"};
			};
		};
	};
};
class CfgPatches
{
    class ExamplePlugin
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]={};
    };
};
