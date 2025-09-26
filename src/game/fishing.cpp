/* 
fishing.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif


/*
Suchen "void Take(fishing_event_info* info, LPCHARACTER ch)"

danach 	
			case 0:
				//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("°í±â°¡ ÀâÇû½À´Ï´Ù! (%s)"), fish_info[info->fish_id].name);
				if (item_vnum)
				{
					FishingSuccess(ch);

					TPacketGCFishing p;
					p.header = HEADER_GC_FISHING;
					p.subheader = FISHING_SUBHEADER_GC_FISH;
					p.info = item_vnum;
					ch->GetDesc()->Packet(&p, sizeof(TPacketGCFishing));

					LPITEM item = ch->AutoGiveItem(item_vnum, 1, -1, false);
					if (item)
					{

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
						BYTE bBattlePassId = ch->GetBattlePassId();
						if (bBattlePassId)
						{
							DWORD dwCount, dwNotUsed;
							if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, CATCH_FISH, &dwNotUsed, &dwCount))
							{
								if (ch->GetMissionProgress(CATCH_FISH, bBattlePassId) < dwCount)
									ch->UpdateMissionProgress(CATCH_FISH, bBattlePassId, 1, dwCount);
							}
						}
#endif


/*
Suchen "void Grill(LPCHARACTER ch, LPITEM item)"

danach 	
		int idx = -1;
		DWORD vnum = item->GetVnum();
		if (vnum >= 27803 && vnum <= 27830)
			idx = vnum - 27800;
		if (vnum >= 27833 && vnum <= 27860)
			idx = vnum - 27830;
		if (idx == -1)
			return;

		int count = item->GetCount();

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		BYTE bBattlePassId = ch->GetBattlePassId();
		if (bBattlePassId)
		{
			DWORD dwCount, dwNotUsed;
			if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, FRY_FISH, &dwNotUsed, &dwCount))
			{
				if (ch->GetMissionProgress(FRY_FISH, bBattlePassId) < dwCount)
					ch->UpdateMissionProgress(FRY_FISH, bBattlePassId, count, dwCount);
			}
		}
#endif