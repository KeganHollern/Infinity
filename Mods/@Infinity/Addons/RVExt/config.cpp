class CfgMods
{
	class Infinity
	{
		dir = "@Infinity";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Infinity";
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
				files[] = {"RVExt/3_Game"};
			};
		};
	};
};
class CfgPatches
{
    class Infinity
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]={};
    };
};
