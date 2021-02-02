proto void SetStringValue(out string result, string new_value, bool use_memcpy = false);
proto string GetValueBack(string val);
proto bool CreateGuid(out string guid);

void TestSetValue()
{
	Print("Test 1");
	working_scope();
	Print("Test 2");
	unsafe_memcpy();
	Print("Test 3");
	test_newstr();
	Print("Tests Compelte");
}
void working_scope()
{
	string a;
	string b = "value!";
	string c = GetValueBack(b);
	SetStringValue(a, b);
	Print(a);
	Print(c);
}
void unsafe_memcpy()
{
	string a;
	string b = "value!";
	SetStringValue(a, b, true);
	Print(a);
}
void test_newstr()
{
	string guid;
	bool worked = CreateGuid(guid);
	if(!worked)
		Print("Failed to create guid!");
	else
		Print(guid);
}