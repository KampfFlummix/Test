/* 
PythonNetworkStreamModule.cpp

davor 	
void initnet()

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
PyObject* netSendBattlePassAction(PyObject* poSelf, PyObject* poArgs)
{
	int iAction = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &iAction))
		return Py_BuildException();

	CPythonNetworkStream::Instance().SendBattlePassAction(iAction);
	return Py_BuildNone();
}
#endif



/*
Suchen "void initnet()
{
	static PyMethodDef s_methods[] ="

davor 	
		{ NULL, NULL, NULL },
	};
	
hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
		{ "SendBattlePassAction", netSendBattlePassAction, METH_VARARGS },
#endif