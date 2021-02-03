class ExamplePluginObject {
	void ExamplePluginObject() { Print("Constructed ExamplePluginObject!"); }
	void ~ExamplePluginObject() { Print("Deconstructed ExamplePluginObject!"); }
	proto native static void TestStaticFunction();
	proto native void NonStaticFunction();
}


void TestClassProtos()
{
	ExamplePluginObject.TestStaticFunction();
	ExamplePluginObject obj = new ExamplePluginObject;
	obj.NonStaticFunction();
}