proto native void NativeTypeTest(typename test_string);
proto void NonNativeTypeTest(typename test_string);
proto void SetOutputValueTest(typename type, out string name);

proto native void WriteToConsole(string text);

proto void RunCallbackTest(Class anyclass);


proto native ScriptModule LoadSpecialModule(ScriptModule parent);