/* 
Main.cpp

darunter 	int g_iItemCacheFlushSeconds = 60 * 5;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
int g_iCurrentBattlePassId = 1;
#endif



/* 

darunter 		if (CConfig::instance().GetValue("CACHE_FLUSH_LIMIT_PER_SECOND", szBuf, 256))
	{
		DWORD dwVal = 0; str_to_number(dwVal, szBuf);
		CClientManager::instance().SetCacheFlushCountLimit(dwVal);
	}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	if (CConfig::instance().GetValue("CURRENT_BATTLE_PASS_ID", szBuf, 256))
	{
		str_to_number(g_iCurrentBattlePassId, szBuf);
		sys_log(0, "CURRENT_BATTLE_PASS_ID: %d", g_iCurrentBattlePassId);
	}
#endif