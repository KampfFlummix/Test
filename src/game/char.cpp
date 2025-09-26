/* 
char.cpp


hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif


/*
Suchen "void CHARACTER::Initialize()"

danach 	m_iSyncHackCount = 0;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	m_listBattlePass.clear();
	m_bIsLoadedBattlePass = false;
	m_dwBattlePassEndTime = 0;
#endif


/*
Suchen "void CHARACTER::CreatePlayerProto(TPlayerTable& tab)"

danach 	thecore_memcpy(tab.skills, m_pSkillLevels, sizeof(TPlayerSkill) * ......

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS
	tab.dwBattlePassEndTime = m_dwBattlePassEndTime;
#endif


/*
Suchen "void CHARACTER::SetPlayerProto(const TPlayerTable* t)"

danach 	if (t->lMapIndex >= 10000)

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS
	m_dwBattlePassEndTime = t->dwBattlePassEndTime;
#endif



/*
Suchen "void CHARACTER::Disconnect(const char* c_pszReason)"

danach 	SaveAffect();
		m_bIsLoadedAffect = false;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	ListBattlePassMap::iterator it = m_listBattlePass.begin();
	while (it != m_listBattlePass.end())
	{
		TPlayerBattlePassMission* pkMission = *it++;

		// if (!pkMission->bIsUpdated)
			// continue;
		
		// sys_err("BATTLE PASS: Saving pid %d | missionID = %d", pkMission->dwPlayerId, pkMission->dwMissionId);
		
		char szBattleQuery[1024];
		snprintf(szBattleQuery, sizeof(szBattleQuery),
			"REPLACE INTO battle_pass%s (player_id, mission_id, battle_pass_id, extra_info, completed) VALUES (%lu, %d, %d, %d, %d)",
			get_table_postfix(),
			pkMission->dwPlayerId,
			pkMission->dwMissionId,
			pkMission->dwBattlePassId,
			pkMission->dwExtraInfo,
			pkMission->bCompleted ? 1 : 0);
		
		DBManager::instance().Query(szBattleQuery);

		// db_clientdesc->DBPacket(HEADER_GD_SAVE_BATTLE_PASS, GetDesc()->GetHandle(), pkMission, sizeof(TPlayerBattlePassMission));
	}
	m_bIsLoadedBattlePass = false;
#endif


/*
Suchen "void CHARACTER::PointChange(BYTE type, int64_t amount, bool bAmount, bool bBroadcast)"

danach 		case POINT_NONE:

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	case POINT_BATTLE_PASS_ID:
#endif



/*
am Ende

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
void CHARACTER::LoadBattlePass(DWORD dwCount, TPlayerBattlePassMission* data)
{
	m_bIsLoadedBattlePass = false;

	for (int i = 0; i < dwCount; ++i, ++data)
	{
		TPlayerBattlePassMission* newMission = new TPlayerBattlePassMission;
		newMission->dwPlayerId = data->dwPlayerId;
		newMission->dwMissionId = data->dwMissionId;
		newMission->dwBattlePassId = data->dwBattlePassId;
		newMission->dwExtraInfo = data->dwExtraInfo;
		newMission->bCompleted = data->bCompleted;
		newMission->bIsUpdated = data->bIsUpdated;

		m_listBattlePass.push_back(newMission);
	}

	m_bIsLoadedBattlePass = true;
}

DWORD CHARACTER::GetMissionProgress(DWORD dwMissionID, DWORD dwBattlePassID)
{
	ListBattlePassMap::iterator it = m_listBattlePass.begin();
	while (it != m_listBattlePass.end())
	{
		TPlayerBattlePassMission* pkMission = *it++;
		if (pkMission->dwMissionId == dwMissionID && pkMission->dwBattlePassId == dwBattlePassID)
			return pkMission->dwExtraInfo;
	}
	return 0;
}

bool CHARACTER::IsCompletedMission(BYTE bMissionType)
{
	ListBattlePassMap::iterator it = m_listBattlePass.begin();
	while (it != m_listBattlePass.end())
	{
		TPlayerBattlePassMission* pkMission = *it++;
		if (pkMission->dwMissionId == bMissionType)
			return (pkMission->bCompleted ? true : false);
	}
	return false;
}

void CHARACTER::UpdateMissionProgress(DWORD dwMissionID, DWORD dwBattlePassID, DWORD dwUpdateValue, DWORD dwTotalValue, bool isOverride)
{
	if (!m_bIsLoadedBattlePass)
		return;

	bool foundMission = false;
	DWORD dwSaveProgress = 0;

	ListBattlePassMap::iterator it = m_listBattlePass.begin();
	while (it != m_listBattlePass.end())
	{
		TPlayerBattlePassMission* pkMission = *it++;

		if (pkMission->dwMissionId == dwMissionID && pkMission->dwBattlePassId == dwBattlePassID)
		{
			pkMission->bIsUpdated = 1;

			if (isOverride)
				pkMission->dwExtraInfo = dwUpdateValue;
			else
				pkMission->dwExtraInfo += dwUpdateValue;

			if (pkMission->dwExtraInfo >= dwTotalValue)
			{
				pkMission->dwExtraInfo = dwTotalValue;
				pkMission->bCompleted = 1;

				std::string stMissionName = CBattlePass::instance().GetMissionNameByType(pkMission->dwMissionId);
				std::string stBattlePassName = CBattlePass::instance().GetBattlePassNameByID(pkMission->dwBattlePassId);
				ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("Vous avez terminé une mission du Pass de combat"));

				CBattlePass::instance().BattlePassRewardMission(this, dwMissionID, dwBattlePassID);
			}

			dwSaveProgress = pkMission->dwExtraInfo;
			foundMission = true;
			break;
		}
	}

	if (!foundMission)
	{
		TPlayerBattlePassMission* newMission = new TPlayerBattlePassMission;
		newMission->dwPlayerId = GetPlayerID();
		newMission->dwMissionId = dwMissionID;
		newMission->dwBattlePassId = dwBattlePassID;

		if (dwUpdateValue >= dwTotalValue)
		{
			newMission->dwExtraInfo = dwTotalValue;
			newMission->bCompleted = 1;

			CBattlePass::instance().BattlePassRewardMission(this, dwMissionID, dwBattlePassID);

			dwSaveProgress = dwTotalValue;
		}
		else
		{
			newMission->dwExtraInfo = dwUpdateValue;
			newMission->bCompleted = 0;

			dwSaveProgress = dwUpdateValue;
		}

		newMission->bIsUpdated = 1;

		m_listBattlePass.push_back(newMission);
	}

	if (!GetDesc())
		return;

	TPacketGCBattlePassUpdate packet;
	packet.bHeader = HEADER_GC_BATTLE_PASS_UPDATE;
	packet.bMissionType = dwMissionID;
	packet.dwNewProgress = dwSaveProgress;
	GetDesc()->Packet(&packet, sizeof(TPacketGCBattlePassUpdate));
}

BYTE CHARACTER::GetBattlePassId()
{
	CAffect* pAffect = FindAffect(AFFECT_BATTLE_PASS, POINT_BATTLE_PASS_ID);

	if (!pAffect)
		return 0;

	return pAffect->lApplyValue;
}

int CHARACTER::GetSecondsTillNextMonth()
{
	time_t iTime;
	time(&iTime);
	struct tm endTime = *localtime(&iTime);

	int iCurrentMonth = endTime.tm_mon;

	endTime.tm_hour = 0; 
	endTime.tm_min = 0; 
	endTime.tm_sec = 0;
	endTime.tm_mday = 1;

	if (iCurrentMonth == 12)
	{
		endTime.tm_mon = 0;
		endTime.tm_year = endTime.tm_year + 1;
	}
	else
	{
		endTime.tm_mon = iCurrentMonth + 1;
	}

	int seconds = difftime(mktime(&endTime), iTime);
	
	return seconds;
}
#endif















