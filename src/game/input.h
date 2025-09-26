/* 
input.h

Suchen "class CInputMain : public CInputProcessor /> protected:"

danach 	
	void UseSkill(LPCHARACTER ch, const char* pcData);


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	int BattlePass(LPCHARACTER ch, const char* data, size_t uiBytes);
#endif


/*
Suchen "class CInputDB : public CInputProcessor  /> protected:"

danach 		void AffectLoad(LPDESC d, const char* c_pData);

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	void BattlePassLoad(LPDESC d, const char* c_pData);
	void BattlePassLoadRanking(LPDESC d, const char* c_pData);
#endif