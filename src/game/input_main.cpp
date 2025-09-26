/* 
input_main.cpp

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif



/*
vor 	
int CInputMain::Shop(LPCHARACTER ch, const char* data, size_t uiBytes)

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
int CInputMain::BattlePass(LPCHARACTER ch, const char* data, size_t uiBytes)
{
	TPacketCGBattlePassAction* p = (TPacketCGBattlePassAction*)data;

	if (uiBytes < sizeof(TPacketCGBattlePassAction))
		return -1;

	const char* c_pData = data + sizeof(TPacketCGBattlePassAction);
	uiBytes -= sizeof(TPacketCGBattlePassAction);

	switch (p->bAction)
	{
	case 1:
		CBattlePass::instance().BattlePassRequestOpen(ch);
		break;

	case 2:
		CBattlePass::instance().BattlePassRequestReward(ch);
		break;

	case 3:
	{
		DWORD dwPlayerId = ch->GetPlayerID();
		BYTE bIsGlobal = 0;

		db_clientdesc->DBPacketHeader(HEADER_GD_BATTLE_PASS_RANKING, ch->GetDesc()->GetHandle(), sizeof(DWORD) + sizeof(BYTE));
		db_clientdesc->Packet(&dwPlayerId, sizeof(DWORD));
		db_clientdesc->Packet(&bIsGlobal, sizeof(BYTE));
	}
	break;

	default:
		break;
	}

	return 0;
}
#endif



/*
Suchen "int CInputMain::Analyze(LPDESC d, BYTE bHeader, const char* c_pData)"

danach 	
	case HEADER_CG_DRAGON_SOUL_REFINE:
	{
		TPacketCGDragonSoulRefine* p = reinterpret_cast <TPacketCGDragonSoulRefine*>((void*)c_pData);
		switch (p->bSubType)
		{
		case DS_SUB_HEADER_CLOSE:
			ch->DragonSoul_RefineWindow_Close();
			break;
		case DS_SUB_HEADER_DO_REFINE_GRADE:
		{
			DSManager::instance().DoRefineGrade(ch, p->ItemGrid);
		}
		break;
		case DS_SUB_HEADER_DO_REFINE_STEP:
		{
			DSManager::instance().DoRefineStep(ch, p->ItemGrid);
		}
		break;
		case DS_SUB_HEADER_DO_REFINE_STRENGTH:
		{
			DSManager::instance().DoRefineStrength(ch, p->ItemGrid);
		}
		break;
		}
	}
	break;

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	case HEADER_CG_BATTLE_PASS:
		if ((iExtraLen = BattlePass(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;
#endif