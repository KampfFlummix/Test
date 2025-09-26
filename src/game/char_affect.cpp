/* 
char_affect.cpp


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "int CHARACTER::ProcessAffect()"

danach 		
for (int i = 0; i <= PREMIUM_MAX_NUM; ++i)
	{
		....
	}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	pkAff = FindAffect(AFFECT_BATTLE_PASS);
	if (pkAff)
	{
		int remain = GetBattlePassEndTime();
		
		if (remain < 0)
		{
			RemoveAffect(AFFECT_BATTLE_PASS);
			m_dwBattlePassEndTime = 0;
			bDiff = true;
		}
		else
			pkAff->lDuration = remain + 1;
	}
#endif