/* 
PythonWindowManagerModulecpp

Suchen "bool PyTuple_GetWindow(PyObject* poArgs, int pos, UI::CWindow** ppRetWindow)"

davor 	
void initwndMgr()

hinzufügen : 
*/

#if defined(ENABLE_IMAGE_CLIP_RECT) || defined(ENABLE_BATTLE_PASS_SYSTEM)
PyObject* wndSetClipRect(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	float fLeft;
	if (!PyTuple_GetFloat(poArgs, 1, &fLeft))
		return Py_BuildException();
	float fTop;
	if (!PyTuple_GetFloat(poArgs, 2, &fTop))
		return Py_BuildException();
	float fRight;
	if (!PyTuple_GetFloat(poArgs, 3, &fRight))
		return Py_BuildException();
	float fBottom;
	if (!PyTuple_GetFloat(poArgs, 4, &fBottom))
		return Py_BuildException();
	int isVertical;
	if (!PyTuple_GetInteger(poArgs, 5, &isVertical))
		return Py_BuildException();

	if (pWindow->IsType(UI::CExpandedImageBox::Type()))
		((UI::CExpandedImageBox*)pWindow)->SetImageClipRect(fLeft, fTop, fRight, fBottom, isVertical ? true : false);

	return Py_BuildNone();
}
#endif



/*
Suchen "void initwndMgr()"

davor	
		{ NULL, NULL, NULL },
	};

	PyObject* poModule = Py_InitModule("wndMgr", s_methods);
	
hinzufügen : 
*/

#if defined(ENABLE_IMAGE_CLIP_RECT) || defined(ENABLE_BATTLE_PASS_SYSTEM)
		{ "SetClipRect", wndSetClipRect, METH_VARARGS },
#endif