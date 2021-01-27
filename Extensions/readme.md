HttpGet
==========
HttpGet is a simple web request extension. This lets your server communicate with an HTTP server through GET requests. 


### Adding HttpGet to your Mod Files
	Add HttpGet.pbo or the interface.c file to your mod files.

### Adding HttpGet to your Server
	Place HttpGet.dll in the root folder of your dayz server (Next to DayZServer_x64.dll)

### HttpGet in Enforce
```
string result = HttpGet("http://your.url.here/api.php");
```
