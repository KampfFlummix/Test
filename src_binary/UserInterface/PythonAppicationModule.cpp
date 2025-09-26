/* 
PythonApplicationModule.cpp

am Ende

davor 	
#ifdef USE_OPENID
	PyModule_AddIntConstant(poModule, "USE_OPENID", 1);
	if (openid_test)
		PyModule_AddIntConstant(poModule, "OPENID_TEST", 1);
	else
		PyModule_AddIntConstant(poModule, "OPENID_TEST", 0);
#else
	PyModule_AddIntConstant(poModule, "USE_OPENID", 0);
	PyModule_AddIntConstant(poModule, "OPENID_TEST", 0);
#endif /* USE_OPENID 

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_BATTLE_PASS_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_BATTLE_PASS_SYSTEM", 0);
#endif

