
class Extension
{
	protected string _Library;
	
	
	void Extension(string Library)
	{
		_Library = Library;
	}
	
	string CallExtensionDZ(string function, string argument)
	{
		return CallDZ(_Library,function, argument);
	}
	string CallExtensionRV(string function)
	{
		return CallRV(_Library, function);
	}
	string CallExtensionRVArgs(string function, notnull array<string> args)
	{
		return CallRVArgs(_Library, function, args, args.Count());
	}
	string GetVersion()
	{
		return CallRVVer(_Library);
	}
	

};

proto native string CallDZ(string library, string function, string arguments);
proto native string CallRVVer(string library);
proto native string CallRV(string library, string function);
proto native string CallRVArgs(string library, string function, notnull array<string> args, int argsCount);
