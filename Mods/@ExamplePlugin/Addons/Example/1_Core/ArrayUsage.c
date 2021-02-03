proto native void PrintStringsFromArray(notnull array<string> arr);
proto native void PrintClassNames(notnull array<Class> arr);
proto native void PrintMapInfo(notnull map<string, Class> arr);

class ArrayTestClass
{
}
class ArrayTestClass2
{
}

void TestArrayUsage()
{
	Print("Testing arrays!");
	array<string> values = new array<string>;
	values.Insert("Hello!");
	values.Insert("Working!");
	
	PrintStringsFromArray(values);
	
	array<Class> values2 = new array<Class>;
	values2.Insert(new ArrayTestClass);
	values2.Insert(new ArrayTestClass2);
	
	PrintClassNames(values2);
	
	
	map<string, Class> values3 = new map<string, Class>;
	values3.Insert("Test Class One",new ArrayTestClass);
	values3.Insert("Test Class Two",new ArrayTestClass2);
	PrintMapInfo(values3);
}