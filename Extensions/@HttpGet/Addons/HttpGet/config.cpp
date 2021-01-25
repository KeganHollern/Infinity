class CfgMods
{
	class HttpGet
	{
		dir = "@HttpGet";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "HttpGet";
		credits = "gallexme";
		author = "Lystic";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"HttpGet/3_Game"};
			};
		};
	};
};
class CfgPatches
{
    class HttpGet
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]={};
    };
};
