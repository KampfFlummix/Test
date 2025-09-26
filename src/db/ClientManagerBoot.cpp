/* 
ClientManagerBoot.cpp

Suchen "bool CClientManager::InitializeTables()"

darunter 	if (!InitializeObjectTable())
		{
			sys_err("InitializeObjectTable FAILED");
			return false;
		}

hinzufügen : 
*/


#ifdef __BATTLE_PASS_SYSTEM__
	if (!LoadBattlePassRanking())
	{
		sys_err("LoadBattlePassRanking FAILED");
		return false;
	}
#endif