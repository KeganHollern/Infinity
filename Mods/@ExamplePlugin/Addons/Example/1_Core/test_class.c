
class ExampleTestClass {
	//yeah don't recommend trying to use these!
	proto native string GetName();
	static proto native ExampleTestClass Create(string name);
	
	//these should function as of 1/20/2021
	static proto native int GetInternalValue(string string_input);
}