proto void SetABCs(out string a, out string b, out string c);
proto void SetABCs2(out string a, out string b, out string c);

void TestSetValue()
{
	string a1;
	string b1;
	string c1;
	SetABCs(a1,b1,c1);
	Print(a1);
	Print(b1);
	Print(c1);
	
	string a2;
	string b2;
	string c2;
	SetABCs2(a2,b2,c2);
	Print(a2);
	Print(b2);
	Print(c2);
}