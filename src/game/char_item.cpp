/* 
char_item.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen : "bool CHARACTER::DoRefine(LPITEM item, bool bMoneyOnly)"

danach : 		if (pkNewItem)
		{
			ITEM_MANAGER::CopyAllAttrTo(item, pkNewItem);
			LogManager::instance().ItemLog(this, pkNewItem, "REFINE SUCCESS", pkNewItem->GetName());

			UINT bCell = item->GetCell();


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			BYTE bBattlePassId = GetBattlePassId();
			if (bBattlePassId)
			{
				DWORD dwItemVnum, dwCount;
				if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, REFINE_ITEM, &dwItemVnum, &dwCount))
				{
					if (dwItemVnum == item->GetVnum() && GetMissionProgress(REFINE_ITEM, bBattlePassId) < dwCount)
						UpdateMissionProgress(REFINE_ITEM, bBattlePassId, 1, dwCount);
				}
			}
#endif



/*
Suchen : "bool CHARACTER::DoRefineWithScroll(LPITEM item)"

danach : if (pkNewItem)
		{
			LogManager::instance().ItemLog(this, pkNewItem, "REFINE SUCCESS", pkNewItem->GetName());

			UINT bCell = item->GetCell();


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			BYTE bBattlePassId = GetBattlePassId();
			if (bBattlePassId)
			{
				DWORD dwItemVnum, dwCount;
				if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, REFINE_ITEM, &dwItemVnum, &dwCount))
				{
					if (dwItemVnum == item->GetVnum() && GetMissionProgress(REFINE_ITEM, bBattlePassId) < dwCount)
						UpdateMissionProgress(REFINE_ITEM, bBattlePassId, 1, dwCount);
				}
			}
#endif



/*
Suchen : "bool CHARACTER::DoRefineWithScroll(LPITEM item)"

danach : if (pkNewItem)
		{
			LogManager::instance().ItemLog(this, pkNewItem, "REFINE FAIL", pkNewItem->GetName());

			UINT bCell = item->GetCell();


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			BYTE bBattlePassId = GetBattlePassId();
			if (bBattlePassId)
			{
				DWORD dwItemVnum, dwCount;
				if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, REFINE_ITEM, &dwItemVnum, &dwCount))
				{
					if (dwItemVnum == item->GetVnum() && GetMissionProgress(REFINE_ITEM, bBattlePassId) < dwCount)
						UpdateMissionProgress(REFINE_ITEM, bBattlePassId, 1, dwCount);
				}
			}
#endif



/*
Suchen : "bool CHARACTER::UseItemEx(LPITEM item, TItemPos DestCell)"

danach : if (false == item->IsEquipped())
			item->SetSocket(1, item->GetSocket(1) + 1);
	}


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	BYTE bBattlePassId = GetBattlePassId();
	if (bBattlePassId)
	{
		DWORD dwItemVnum, dwUseCount;
		if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, USE_ITEM, &dwItemVnum, &dwUseCount))
		{
			if (dwItemVnum == item->GetVnum() && GetMissionProgress(USE_ITEM, bBattlePassId) < dwUseCount)
				UpdateMissionProgress(USE_ITEM, bBattlePassId, 1, dwUseCount);
		}
	}
#endif


/*

vor : 			case 50004: // ÀÌº¥Æ®¿ë °¨Áö±â

hinzufügen : 
*/

	case 93100:
		{
			char szQuery[1024];
			snprintf(szQuery, sizeof(szQuery), "SELECT * FROM battle_pass_ranking WHERE player_name = '%s' AND battle_pass_id = %d;", GetName(), item->GetValue(0));
			std::unique_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery(szQuery));
			
			if (pmsg->Get()->uiNumRows > 0)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Vous avez déjà compléter ce Pass de combat."));
				return false;
			}
			
			int iSeconds = GetSecondsTillNextMonth();
			
			if(iSeconds < 0)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Erreur système, veuillez contacter un administrateur."));
				return false;
			}
			
			if(FindAffect(AFFECT_BATTLE_PASS))
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Vous avez déjà le Pass de combat d'activer sur ce compte."));
				return false;
			}
			else
			{
				m_dwBattlePassEndTime = get_global_time() + iSeconds;
				
				AddAffect(AFFECT_BATTLE_PASS, POINT_BATTLE_PASS_ID, item->GetValue(0), 0, iSeconds, 0, true);
				ITEM_MANAGER::instance().RemoveItem(item);
			}
		}
		break;


/*
Suchen : "bool CHARACTER::DestroyItem(TItemPos Cell)"

danach : if (item->GetCount() <= 0)
		return false;


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		BYTE bBattlePassId = GetBattlePassId();
		if(bBattlePassId)
		{
			DWORD dwItemVnum, dwDestItemCount;
			if(CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, DESTROY_ITEM, &dwItemVnum, &dwDestItemCount))
			{
				if(dwItemVnum == item->GetVnum() && GetMissionProgress(DESTROY_ITEM, bBattlePassId) < dwDestItemCount)
					UpdateMissionProgress(DESTROY_ITEM, bBattlePassId, 1, dwDestItemCount);
			}
		}
#endif


/*
Suchen : "void CHARACTER::GiveGold(long long llAmount)"

danach : if (llAmount <= 0)
		return;

	sys_log(0, "GIVE_GOLD: %s %lld", GetName(), llAmount);


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	BYTE bBattlePassId = GetBattlePassId();
	if (bBattlePassId)
	{
		DWORD dwYangCount, dwNotUsed;
		if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, FARM_YANG, &dwNotUsed, &dwYangCount))
		{
			if (GetMissionProgress(FARM_YANG, bBattlePassId) < dwYangCount)
				UpdateMissionProgress(FARM_YANG, bBattlePassId, llAmount, dwYangCount);
		}
	}
#endif



/*
Suchen : "bool CHARACTER::PickupItem(DWORD dwVID)"

danach :
	if (!item || !item->GetSectree())
		return false;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	bool bIsBattlePass = item->HaveOwnership();
#endif



/*
Suchen : "bool CHARACTER::PickupItem(DWORD dwVID)"

danach :
						if (item2->GetVnum() == item->GetVnum())
						{
							int j;

							for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
							if (bIsBattlePass)
							{
								BYTE bBattlePassId = GetBattlePassId();
								if (bBattlePassId)
								{
									DWORD dwItemVnum, dwCount;
									if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, COLLECT_ITEM, &dwItemVnum, &dwCount))
									{
										if (dwItemVnum == item->GetVnum() && GetMissionProgress(COLLECT_ITEM, bBattlePassId) < dwCount)
											UpdateMissionProgress(COLLECT_ITEM, bBattlePassId, bCount2, dwCount);
									}
								}
							}
#endif



/*
Suchen : "bool CHARACTER::PickupItem(DWORD dwVID)"

danach :
					for (int i = SKILL_BOOK_INVENTORY_SLOT_START; i < GIFT_BOX_INVENTORY_SLOT_END; ++i)
					{
						LPITEM item2 = GetInventoryItem(i);

						if (!item2)
							continue;

						if (item2->GetVnum() == item->GetVnum())
						{
							int j;

							for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
								if (item2->GetSocket(j) != item->GetSocket(j))
									break;

							if (j != ITEM_SOCKET_MAX_NUM)
								continue;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
							if (bIsBattlePass)
							{
								BYTE bBattlePassId = GetBattlePassId();
								if (bBattlePassId)
								{
									DWORD dwItemVnum, dwCount;
									if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, COLLECT_ITEM, &dwItemVnum, &dwCount))
									{
										if (dwItemVnum == item->GetVnum() && GetMissionProgress(COLLECT_ITEM, bBattlePassId) < dwCount)
											UpdateMissionProgress(COLLECT_ITEM, bBattlePassId, bCount2, dwCount);
									}
								}
							}
#endif		



/*
Suchen : "bool CHARACTER::PickupItem(DWORD dwVID)"

vor :
				char szHint[32 + 1];
				snprintf(szHint, sizeof(szHint), "%s %u %u", item->GetName(), item->GetCount(), item->GetOriginalVnum());
				LogManager::instance().ItemLog(this, item, "GET", szHint);
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¾ÆÀÌÅÛ È¹µæ: %s"), item->GetName());

				// if (item->GetType() == ITEM_QUEST)
				quest::CQuestManager::instance().PickupItem(GetPlayerID(), item);
			}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
				if (bIsBattlePass)
				{
					BYTE bBattlePassId = GetBattlePassId();
					if (bBattlePassId)
					{
						DWORD dwItemVnum, dwCount;
						if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, COLLECT_ITEM, &dwItemVnum, &dwCount))
						{
							if (dwItemVnum == item->GetVnum() && GetMissionProgress(COLLECT_ITEM, bBattlePassId) < dwCount)
								UpdateMissionProgress(COLLECT_ITEM, bBattlePassId, item->GetCount(), dwCount);
						}
					}
				}
#endif



/*
Suchen : "bool CHARACTER::PickupItem(DWORD dwVID)"

vor :
			char szHint[32 + 1];
			snprintf(szHint, sizeof(szHint), "%s %u %u", item->GetName(), item->GetCount(), item->GetOriginalVnum());
			LogManager::instance().ItemLog(owner, item, "GET", szHint);

			if (owner == this)
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¾ÆÀÌÅÛ È¹µæ: %s"), item->GetName());
			else
			{
				owner->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¾ÆÀÌÅÛ È¹µæ: %s ´ÔÀ¸·ÎºÎÅÍ %s"), GetName(), item->GetName());
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¾ÆÀÌÅÛ Àü´Þ: %s ´Ô¿¡°Ô %s"), owner->GetName(), item->GetName());
			}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			if (bIsBattlePass)
			{
				BYTE bBattlePassId = owner->GetBattlePassId();
				if (bBattlePassId)
				{
					DWORD dwItemVnum, dwCount;
					if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, COLLECT_ITEM, &dwItemVnum, &dwCount))
					{
						if (dwItemVnum == item->GetVnum() && owner->GetMissionProgress(COLLECT_ITEM, bBattlePassId) < dwCount)
							owner->UpdateMissionProgress(COLLECT_ITEM, bBattlePassId, item->GetCount(), dwCount);
					}
				}
			}
#endif

