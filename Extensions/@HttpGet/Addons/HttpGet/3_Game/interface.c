string HttpGet(string URL)
{
	Extension ext = new Extension("HttpGet");
	return ext.CallExtensionRV(URL);
}