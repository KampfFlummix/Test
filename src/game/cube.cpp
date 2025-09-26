/* 
cube.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "bool Cube_make(LPCHARACTER ch)"

danach 
	percent_number = number(1, 100);
	if (percent_number <= cube_proto->percent)
	{
		// ¼º°ø
		ch->ChatPacket(CHAT_TYPE_COMMAND, "cube success %d %d", reward_value->vnum, reward_value->count);
		new_item = ch->AutoGiveItem(reward_value->vnum, reward_value->count);
		
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		BYTE bBattlePassId = ch->GetBattlePassId();
		if(bBattlePassId)
		{
			DWORD dwItemVnum, dwCount;
			if(CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, CRAFT_ITEM, &dwItemVnum, &dwCount))
			{
				if(dwItemVnum == reward_value->vnum && ch->GetMissionProgress(CRAFT_ITEM, bBattlePassId) < dwCount)
					ch->UpdateMissionProgress(CRAFT_ITEM, bBattlePassId, 1, dwCount);
			}
		}
#endif