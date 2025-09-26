/* 
cuberenewal.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "void Cube_Make(LPCHARACTER ch, int index, int count_item, int index_item_improve)"

danach 	
				if(total_items_give <= 0)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "Il a echoué.");
					return;
				}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
				BYTE bBattlePassId = ch->GetBattlePassId();
				if(bBattlePassId)
				{
					DWORD dwItemVnum, dwCount;
					if(CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, CRAFT_ITEM, &dwItemVnum, &dwCount))
					{
						if(dwItemVnum == materialInfo.reward.vnum && ch->GetMissionProgress(CRAFT_ITEM, bBattlePassId) < dwCount)
							ch->UpdateMissionProgress(CRAFT_ITEM, bBattlePassId, (materialInfo.reward.count*total_items_give), dwCount);
					}
				}
#endif			