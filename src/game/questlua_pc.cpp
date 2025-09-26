/* 
questlua_pc.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "namespace quest"

danach 	
	int pc_exchanging(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (!ch) return 0;

		if (ch->GetExchange())
			return 1;
		else
			return 0;
	}
	
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	int pc_update_dungeon_progress(lua_State* L)
	{
		if (!lua_isnumber(L, 1))
		{
			sys_err("arg1 must be number");
			return 0;
		}

		BYTE bDungeonType = (int)lua_tonumber(L, 1);
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();

		if (ch)
		{
			BYTE bBattlePassId = ch->GetBattlePassId();
			if (bBattlePassId)
			{
				DWORD dwDungeonID, dwCount;
				if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, COMPLETE_DUNGEON, &dwDungeonID, &dwCount))
				{
					if (dwDungeonID == bDungeonType && ch->GetMissionProgress(COMPLETE_DUNGEON, bBattlePassId) < dwCount)
						ch->UpdateMissionProgress(COMPLETE_DUNGEON, bBattlePassId, 1, dwCount);
				}
			}
		}

		return 0;
	}

	int pc_open_battle_pass_ranking(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
		{
			DWORD dwPlayerId = ch->GetPlayerID();
			BYTE bIsGlobal = 1;

			db_clientdesc->DBPacketHeader(HEADER_GD_BATTLE_PASS_RANKING, ch->GetDesc()->GetHandle(), sizeof(DWORD) + sizeof(BYTE));
			db_clientdesc->Packet(&dwPlayerId, sizeof(DWORD));
			db_clientdesc->Packet(&bIsGlobal, sizeof(BYTE));
		}

		return 0;
	}
#endif



/*
am Ende

vor 	
			{ NULL, NULL }
		};

		CQuestManager::instance().AddLuaFunctionTable("pc", pc_functions);
	}
};
	
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			{ "update_dungeon_progress", pc_update_dungeon_progress },
			{ "open_battle_pass_ranking", pc_open_battle_pass_ranking },
#endif