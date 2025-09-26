/* 
shop.cpp

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "int CShop::Buy(LPCHARACTER ch, BYTE pos)"

danach 	

	if (iEmptyPos < 0)
	{
		if (m_pkPC)
		{
			sys_log(1, "Shop::Buy at PC Shop : Inventory full : %s size %d", ch->GetName(), item->GetSize());
			return SHOP_SUBHEADER_GC_INVENTORY_FULL;
		}
		else
		{
			sys_log(1, "Shop::Buy : Inventory full : %s size %d", ch->GetName(), item->GetSize());
			M2_DESTROY_ITEM(item);
			return SHOP_SUBHEADER_GC_INVENTORY_FULL;
		}
	}

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	bool bIsBattlePass = false;
	long dwPriceCount = 0;
#endif



/*
Suchen "int CShop::Buy(LPCHARACTER ch, BYTE pos)"

danach 	
ch->PointChange(POINT_GOLD, -llPrice, false);

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	if (m_pkPC)
	{
		bIsBattlePass = true;
		dwPriceCount = llPrice;
	}
#endif



/*
Suchen "int CShop::Buy(LPCHARACTER ch, BYTE pos)"

danach 	
		if (iVal > 0)
			m_pkPC->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�Ǹűݾ��� %d %% �� �������� �����Ե˴ϴ�"), iVal);

		CMonarch::instance().SendtoDBAddMoney(dwTax, m_pkPC->GetEmpire(), m_pkPC);
	}
	else
	{

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		if(bIsBattlePass)
		{
			BYTE bBattlePassId = ch->GetBattlePassId();
			if(bBattlePassId)
			{
				DWORD dwYangCount, dwNotUsed;
				if(CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, SPENT_YANG, &dwNotUsed, &dwYangCount))
				{
					if(ch->GetMissionProgress(SPENT_YANG, bBattlePassId) < dwYangCount)
						ch->UpdateMissionProgress(SPENT_YANG, bBattlePassId, dwPriceCount, dwYangCount);
				}
			}
		}
#endif	