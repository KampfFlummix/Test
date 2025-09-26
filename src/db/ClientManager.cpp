/* 
ClientManager.cpp

Suchen "void CClientManager::ProcessPackets(CPeer* peer)"

darunter 		case HEADER_GD_REQUEST_CHANNELSTATUS:
			RequestChannelStatus(peer, dwHandle);
			break;

unten hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		case HEADER_GD_SAVE_BATTLE_PASS:
			// sys_err("HEADER_GD_SAVE_BATTLE_PASS (handle: %d length: %d)", dwHandle, dwLength);
			QUERY_SAVE_BATTLE_PASS(peer, dwHandle, (TPlayerBattlePassMission*)data);
			break;
			
			sys_log(1, "HEADER_GD_PLAYER_SAVE (handle: %d length: %d)", dwHandle, dwLength);
			QUERY_PLAYER_SAVE(peer, dwHandle, (TPlayerTable*)data);

		case HEADER_GD_REGISTER_BP_RANKING:
			QUERY_REGISTER_RANKING(peer, dwHandle, (TBattlePassRegisterRanking*)data);
			break;

		case HEADER_GD_BATTLE_PASS_RANKING:
			RequestLoadBattlePassRanking(peer, dwHandle, data);
			break;
#endif



/* 
Suchen "int CClientManager::AnalyzeQueryResult(SQLMsg* msg)"

darunter 		case QID_AFFECT:

unten hinzufügen  :
*/

#ifdef __BATTLE_PASS_SYSTEM__
	case QID_BATTLE_PASS:
#endif



/* 
Suchen "int CClientManager::Process()"

darunter 	if (!(thecore_heart->pulse % (thecore_heart->passes_per_sec * 3600))) // ÇÑ½Ã°£¿¡ ÇÑ¹ø
		{
			CMoneyLog::instance().Save();
		}

unten hinzufügen  :
*/

#ifdef __BATTLE_PASS_SYSTEM__
		if (!(thecore_heart->pulse % (thecore_heart->passes_per_sec * 3600))) // Refresh ranking cache every hour
		{
			CClientManager::instance().LoadBattlePassRanking();
		}
#endif



