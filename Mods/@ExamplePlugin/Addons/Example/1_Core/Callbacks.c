
class CallbackTest {
	void Callback() { Print("Running Callback On New Thread!"); }
}

proto native void RunCallbackTest(CallbackTest test);

void TestCallbacks() {
	CallbackTest test = new CallbackTest;
	RunCallbackTest(test);
}
