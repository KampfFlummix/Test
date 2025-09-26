/* 
input_db.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
Suchen "void CInputDB::ItemLoad(LPDESC d, const char* c_pData)"

danach	
	sys_log(0, "LoadLocaleFile: DragonSoulTable: %s", szDragonSoulTableFileName);
	if (!DSManager::instance().ReadDragonSoulTableFile(szDragonSoulTableFileName))
	{
		sys_err("cannot load DragonSoulTable: %s", szDragonSoulTableFileName);
		// thecore_shutdown();
		// return;
	}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	if (!CBattlePass::instance().ReadBattlePassFile())
		sys_err("Cannot load battle_pass.txt");
#endif



/*
vor 	
void CInputDB::AffectLoad(LPDESC d, const char* c_pData)

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
void CInputDB::BattlePassLoad(LPDESC d, const char* c_pData)
{
	if (!d || !d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();
	if (!ch)
		return;

	DWORD dwPID = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	DWORD dwCount = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	if (ch->GetPlayerID() != dwPID)
		return;

	ch->LoadBattlePass(dwCount, (TPlayerBattlePassMission*)c_pData);
}

void CInputDB::BattlePassLoadRanking(LPDESC d, const char* c_pData)
{
	if (!d || !d->GetCharacter())
		return;

	LPCHARACTER ch = d->GetCharacter();
	if (!ch)
		return;

	DWORD dwPID = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	BYTE bIsGlobal = decode_byte(c_pData);
	c_pData += sizeof(BYTE);

	DWORD dwCount = decode_4bytes(c_pData);
	c_pData += sizeof(DWORD);

	sys_err("BattlePassLoadRanking count %d playerid %d", dwCount, dwPID);

	if (ch->GetPlayerID() != dwPID)
		return;

	if (dwCount)
	{
		std::vector<TBattlePassRanking> sendVector;
		sendVector.resize(dwCount);

		TBattlePassRanking* p = (TBattlePassRanking*)c_pData;

		for (int i = 0; i < dwCount; ++i, ++p)
		{
			TBattlePassRanking newRanking;
			newRanking.bPos = p->bPos;
			strlcpy(newRanking.playerName, p->playerName, sizeof(newRanking.playerName));
			newRanking.dwFinishTime = p->dwFinishTime;

			sendVector.push_back(newRanking);
		}

		if (!sendVector.empty())
		{
			TPacketGCBattlePassRanking packet;
			packet.bHeader = HEADER_GC_BATTLE_PASS_RANKING;
			packet.wSize = sizeof(packet) + sizeof(TBattlePassRanking) * sendVector.size();
			packet.bIsGlobal = bIsGlobal;

			ch->GetDesc()->BufferedPacket(&packet, sizeof(packet));
			ch->GetDesc()->Packet(&sendVector[0], sizeof(TBattlePassRanking) * sendVector.size());
		}
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Il n'y aucun classement d'enregistré actuellement");
	}
}
#endif



/*
Suchen "int CInputDB::Analyze(LPDESC d, BYTE bHeader, const char* c_pData)"

vor 	
	default:
		return (-1);
	}

	return 0;
}

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	case HEADER_DG_BATTLE_PASS_LOAD:
		BattlePassLoad(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

	case HEADER_DG_BATTLE_PASS_LOAD_RANKING:
		BattlePassLoadRanking(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif