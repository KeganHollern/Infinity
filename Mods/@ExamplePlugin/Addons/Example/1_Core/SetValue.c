proto void SetABCs(out string a, out string b, out string c);
proto void SetABCs2(out string a, out string b, out string c);

void TestSetValue()
{
	Print("Testing Set 2!");
	scope_2();
	Print("Released Successfully 2!");
	
	//Print("Testing Set!");
	//scope_1();
	//Print("Released Successfully!");
	
}
void scope_1()
{
	string a1;
	string b1;
	string c1;
	SetABCs(a1,b1,c1);
	Print(a1);
	Print(b1);
	Print(c1);
}
void scope_2()
{
	string a2;
	string b2;
	string c2;
	SetABCs2(a2,b2,c2);
	Print(a2);
	Print(b2);
	Print(c2);
}