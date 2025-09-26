/* 
ClientManager.h

Suchenr 		void RESULT_AFFECT_LOAD(CPeer* pkPeer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwRealPID);

unten hinzufügen: 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	void RESULT_BATTLE_PASS_LOAD(CPeer* peer, MYSQL_RES* pRes, DWORD dwHandle, DWORD dwRealPID);
	void QUERY_SAVE_BATTLE_PASS(CPeer* peer, DWORD dwHandle, TPlayerBattlePassMission* battlePass);
	void QUERY_REGISTER_RANKING(CPeer* peer, DWORD dwHandle, TBattlePassRegisterRanking* pRanking);

	bool LoadBattlePassRanking();
	void RequestLoadBattlePassRanking(CPeer* peer, DWORD dwHandle, const char* data);
#endif



/*
Suchenr 		TItemCacheSetPtrMap m_map_pkItemCacheSetPtr;

unten hinzufügen: 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	std::vector<TBattlePassRanking*> m_vec_battlePassRanking;
#endif















