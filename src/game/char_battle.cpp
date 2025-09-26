/*
char_battle.cpp

hinzufügen :
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "void CHARACTER::Reward(bool bItemDrop)"

Cherche : 
	if (pkAttacker->IsPC())
	{
		if (GetLevel() - pkAttacker->GetLevel() >= -10)
			if (pkAttacker->GetRealAlignment() < 0)
			{
				if (pkAttacker->IsEquipUniqueItem(UNIQUE_ITEM_FASTER_ALIGNMENT_UP_BY_KILL))
					pkAttacker->UpdateAlignment(14);
				else
					pkAttacker->UpdateAlignment(7);
			}
			else
				pkAttacker->UpdateAlignment(2);

		pkAttacker->SetQuestNPCID(GetVID());
		quest::CQuestManager::instance().Kill(pkAttacker->GetPlayerID(), GetRaceNum());
		CHARACTER_MANAGER::instance().KillLog(GetRaceNum());

hinzufügen en dessous :
*/

#ifdef __BATTLE_PASS_SYSTEM__
		BYTE bBattlePassId = pkAttacker->GetBattlePassId();
		if (bBattlePassId)
		{
			DWORD dwMonsterVnum, dwToKillCount;
			if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, MONSTER_KILL, &dwMonsterVnum, &dwToKillCount))
			{
				if (dwMonsterVnum == GetRaceNum() && pkAttacker->GetMissionProgress(MONSTER_KILL, bBattlePassId) < dwToKillCount)
					pkAttacker->UpdateMissionProgress(MONSTER_KILL, bBattlePassId, 1, dwToKillCount);
			}
		}
#endif



/*
Suchen "void CHARACTER::Dead(LPCHARACTER pkKiller, bool bImmediateDead)"

Cherche : 
				char buf[256];
				snprintf(buf, sizeof(buf),
					"%d %d %d %s %d %d %d %s",
					GetEmpire(), GetAlignment(), GetPKMode(), GetName(),
					pkKiller->GetEmpire(), pkKiller->GetAlignment(), pkKiller->GetPKMode(), pkKiller->GetName());

				LogManager::instance().CharLog(this, pkKiller->GetPlayerID(), "DEAD_BY_PC", buf);
			}

hinzufügen en dessous :
*/

#ifdef __BATTLE_PASS_SYSTEM__
			BYTE bBattlePassId = pkKiller->GetBattlePassId();
			if (bBattlePassId)
			{
				DWORD dwMinLevel, dwToKillCount;
				if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, PLAYER_KILL, &dwMinLevel, &dwToKillCount))
				{
					if (GetLevel() >= dwMinLevel && pkKiller->GetMissionProgress(PLAYER_KILL, bBattlePassId) < dwToKillCount)
						pkKiller->UpdateMissionProgress(PLAYER_KILL, bBattlePassId, 1, dwToKillCount);
				}
			}
#endif




/*
Suchen "bool CHARACTER::Damage(LPCHARACTER pAttacker, int dam, EDamageType type"

Cherche : 
		else
			damageFlag = DAMAGE_NORMAL;

		if (IsCritical == true)
			damageFlag |= DAMAGE_CRITICAL;

		if (IsPenetrate == true)
			damageFlag |= DAMAGE_PENETRATE;

		// ÃÖÁ¾ µ¥¹ÌÁö º¸Á¤
		float damMul = this->GetDamMul();
		float tempDam = dam;
		dam = tempDam * damMul + 0.5f;

hinzufügen en dessous :
*/

#ifdef __BATTLE_PASS_SYSTEM__
		if (dam > 0)
		{
			BYTE bBattlePassId = pAttacker->GetBattlePassId();
			if (bBattlePassId)
			{
				//if ((damageFlag == DAMAGE_NORMAL || damageFlag & DAMAGE_CRITICAL || damageFlag & DAMAGE_PENETRATE) &&
				//	type != DAMAGE_TYPE_SPECIAL && type != DAMAGE_TYPE_MELEE && type != DAMAGE_TYPE_RANGE && type != DAMAGE_TYPE_MAGIC)
				{
					if (IsPC())
					{
						DWORD dwMinLevel, dwDamage;
						if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, PLAYER_DAMAGE, &dwMinLevel, &dwDamage))
						{
							DWORD dwCurrentDamage = pAttacker->GetMissionProgress(PLAYER_DAMAGE, bBattlePassId);
							if (GetLevel() >= dwMinLevel && dwCurrentDamage < dwDamage && dwCurrentDamage < dam)
								pAttacker->UpdateMissionProgress(PLAYER_DAMAGE, bBattlePassId, dam, dwDamage, true);
						}
					}
					else
					{
						DWORD dwMonsterVnum, dwDamage;
						if (CBattlePass::instance().BattlePassMissionGetInfo(bBattlePassId, MONSTER_DAMAGE, &dwMonsterVnum, &dwDamage))
						{
							DWORD dwCurrentDamage = pAttacker->GetMissionProgress(MONSTER_DAMAGE, bBattlePassId);
							if (dwMonsterVnum == GetRaceNum() && dwCurrentDamage < dwDamage && dwCurrentDamage < dam)
								pAttacker->UpdateMissionProgress(MONSTER_DAMAGE, bBattlePassId, dam, dwDamage, true);
						}
					}
				}
			}
		}
#endif