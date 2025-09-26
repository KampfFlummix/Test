/* 
shop_manager.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "void CShopManager::Sell(LPCHARACTER ch, WORD wCell, BYTE bCount, BYTE bType)"

danach 	
	DBManager::instance().SendMoneyLog(MONEY_LOG_SHOP, item->GetVnum(), dwPrice);

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	BYTE bBattlePassId = ch->GetBattlePassId();
	if(bBattlePassId)
	{
		DWORD dwItemVnum, dwSellCount;
		if(CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, SELL_ITEM, &dwItemVnum, &dwSellCount))
		{
			if(dwItemVnum == item->GetVnum() && ch->GetMissionProgress(SELL_ITEM, bBattlePassId) < dwSellCount)
				ch->UpdateMissionProgress(SELL_ITEM, bBattlePassId, bCount, dwSellCount);
		}
	}
#endif