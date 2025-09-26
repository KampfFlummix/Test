/* 
ClientManagerPlayer.cpp

Suchen "void CClientManager::QUERY_PLAYER_LOAD(CPeer* peer, DWORD dwHandle, TPlayerLoadPacket* packet)"

darunter 		snprintf(queryStr, sizeof(queryStr),
			"SELECT dwPID,bType,bApplyOn,lApplyValue,dwFlag,lDuration,lSPCost FROM affect%s WHERE dwPID=%d",
			GetTablePostfix(), packet->player_id);
		CDBManager::instance().ReturnQuery(queryStr, QID_AFFECT, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
	}

unten hinzufügen:
*/

#ifdef __BATTLE_PASS_SYSTEM__
	// Load all missions from table
	char queryStrBP[QUERY_MAX_LEN];
	snprintf(queryStrBP, sizeof(queryStrBP),
		"SELECT player_id, mission_id, battle_pass_id, extra_info, completed FROM battle_pass WHERE player_id = %d", packet->player_id);
	CDBManager::instance().ReturnQuery(queryStrBP, QID_BATTLE_PASS, peer->GetHandle(), new ClientHandleInfo(dwHandle, packet->player_id));
#endif



/* 
Suchen "int CClientManager::AnalyzeQueryResult(SQLMsg* msg)"

darunter 			case QID_AFFECT:
			sys_log(0, "QID_AFFECT %u", info->dwHandle);
			RESULT_AFFECT_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
			break;

hinzufügen :
*/

#ifdef __BATTLE_PASS_SYSTEM__
	case QID_BATTLE_PASS:
		sys_log(0, "QID_BATTLE_PASS %u", info->dwHandle);
		RESULT_BATTLE_PASS_LOAD(peer, pSQLResult, info->dwHandle, info->player_id);
		break;
#endif


/* 

Funktion suchen : size_t CreatePlayerSaveQuery(char * pszQuery ... 

darunter : "horse_skill_point = %d, "

davor : ,GetTablePostfix(),

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
			"battle_pass_end = FROM_UNIXTIME(%d), "
#endif


/* 

Funktion suchen : size_t CreatePlayerSaveQuery(char * pszQuery ...

Suchen : ");static char text[8192 + 1];"

davor
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
		pkTab->dwBattlePassEndTime
#endif

// Aufpassen es muss innerhalb der Funktion sein


/* 

Funktion suchen : size_t CreatePlayerSaveQuery(char * pszQuery ...

Suchen : 
		sys_log(0, "[PLAYER_LOAD] Load from PlayerDB pid[%d]", packet->player_id);

		char queryStr[QUERY_MAX_LEN];

		snprintf(queryStr, sizeof(queryStr),
				"SELECT "
				"id,name,job,voice,dir,x,y,z,map_index,exit_x,exit_y,exit_map_index,hp,mp,stamina,random_hp,random_sp,playtime,gold," 

davor :  ("FROM player%s WHERE id=%d",)
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
				",UNIX_TIMESTAMP(battle_pass_end) "
#endif


/* 

Suchen : bool CreatePlayerTableFromRes(MYSQL_RES* res, TPlayerTable* pkTab)

Suchen : 
	{
		pkTab->skills[123].bLevel = 0; // SKILL_CREATE

davor
hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	str_to_number(pkTab->dwBattlePassEndTime, row[col++]);
#endif


/* 

darüber	void CClientManager::QUERY_PLAYER_SAVE(CPeer* peer, DWORD dwHandle, TPlayerTable* pkTab)
		{
			if (g_test_server)
			sys_log(0, "PLAYER_SAVE: %s", pkTab->name);

		PutPlayerCache(pkTab);
		}

		typedef std::map<DWORD, time_t> time_by_id_map_t;
		static time_by_id_map_t s_createTimeByAccountID;

hinzufügen :
*/

#ifdef __BATTLE_PASS_SYSTEM__
void CClientManager::RESULT_BATTLE_PASS_LOAD(CPeer * peer, MYSQL_RES * pRes, DWORD dwHandle, DWORD dwRealPID)
{
	int iNumRows;

	if ((iNumRows = mysql_num_rows(pRes)) == 0)
	{
		DWORD dwCount = 0;
		TPlayerBattlePassMission pbpTable = {0};
        
		sys_log(0, "BATTLE_PASS_LOAD: count %u PID %u", dwCount, dwRealPID);
        
		peer->EncodeHeader(HEADER_DG_BATTLE_PASS_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPlayerBattlePassMission) * dwCount);
		peer->Encode(&dwRealPID, sizeof(DWORD));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&pbpTable, sizeof(TPlayerBattlePassMission) * dwCount);
		return;
	}

	static std::vector<TPlayerBattlePassMission> s_mission;
	s_mission.resize(iNumRows);

	MYSQL_ROW row;

	for (int i = 0; i < iNumRows; ++i)
	{
		int	col = 0;
		TPlayerBattlePassMission & r = s_mission[i];
		row = mysql_fetch_row(pRes);

		str_to_number(r.dwPlayerId, row[col++]);
		str_to_number(r.dwMissionId, row[col++]);
		str_to_number(r.dwBattlePassId, row[col++]);
		str_to_number(r.dwExtraInfo, row[col++]);
		str_to_number(r.bCompleted, row[col++]);
		
		r.bIsUpdated = 0;
	}

	sys_log(0, "BATTLE_PASS_LOAD: count %d PID %u", s_mission.size(), dwRealPID);

	DWORD dwCount = s_mission.size();

	peer->EncodeHeader(HEADER_DG_BATTLE_PASS_LOAD, dwHandle, sizeof(DWORD) + sizeof(DWORD) + sizeof(TPlayerBattlePassMission) * dwCount);
	peer->Encode(&dwRealPID, sizeof(DWORD));
	peer->Encode(&dwCount, sizeof(DWORD));
	peer->Encode(&s_mission[0], sizeof(TPlayerBattlePassMission) * dwCount);
}

void CClientManager::QUERY_SAVE_BATTLE_PASS(CPeer * peer, DWORD dwHandle, TPlayerBattlePassMission* battlePass)
{
	// sys_err("DB Battle pass saving - pid %d | mission %d isCompleted %d", 
		// battlePass->dwPlayerId,
		// battlePass->dwMissionId,
		// battlePass->bCompleted ? 1 : 0);
		
	if (g_test_server)
		sys_log(0, "QUERY_SAVE_BATTLE_PASS: %lu", battlePass->dwPlayerId);

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
		"REPLACE INTO battle_pass%s (player_id, mission_id, battle_pass_id, extra_info, completed) VALUES (%lu, %d, %d, %d, %d)",
		GetTablePostfix(),
		battlePass->dwPlayerId,
		battlePass->dwMissionId,
		battlePass->dwBattlePassId,
		battlePass->dwExtraInfo,
		battlePass->bCompleted ? 1 : 0);
		
	CDBManager::instance().AsyncQuery(szQuery);
}

extern int g_iCurrentBattlePassId;
bool CClientManager::LoadBattlePassRanking()
{
	char query[256];
	snprintf(query, sizeof(query), "SELECT player_name, UNIX_TIMESTAMP(finish_time) "
				"FROM battle_pass_ranking WHERE battle_pass_id = %d ORDER BY finish_time ASC LIMIT 45;", g_iCurrentBattlePassId);
	
	std::unique_ptr<SQLMsg> pkMsg(CDBManager::instance().DirectQuery(query));
	SQLResult * pRes = pkMsg->Get();
	
	if (!pRes->uiNumRows)
		return true; // No ranking for battle pass with id %i%

	if(!m_vec_battlePassRanking.empty())
		m_vec_battlePassRanking.clear();

	BYTE posContor = 1;
	
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(pRes->pSQLResult)))
	{
		TBattlePassRanking * ranking = new TBattlePassRanking;
		ranking->bPos = posContor;
		strlcpy(ranking->playerName, row[0], sizeof(ranking->playerName));
		str_to_number(ranking->dwFinishTime, row[1]);
		
		m_vec_battlePassRanking.push_back(ranking);
		posContor++;
	}

	return true;
}

void CClientManager::RequestLoadBattlePassRanking(CPeer * peer, DWORD dwHandle, const char* data)
{
	DWORD dwPlayerID = *(DWORD *)data;
	data += sizeof(DWORD);

	BYTE bIsGlobal = *(BYTE *)data;
	data += sizeof(BYTE);
	
	if(m_vec_battlePassRanking.empty())
	{
		DWORD dwCount = 0;
		TBattlePassRanking pbpTable = {0};
        
		sys_log(0, "RequestLoadBattlePassRanking: count %u PID %d", dwCount, dwPlayerID);
        
		peer->EncodeHeader(HEADER_DG_BATTLE_PASS_LOAD_RANKING, dwHandle, sizeof(DWORD) + sizeof(BYTE) + sizeof(DWORD) + sizeof(TBattlePassRanking) * dwCount);
		peer->Encode(&dwPlayerID, sizeof(DWORD));
		peer->Encode(&bIsGlobal, sizeof(BYTE));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&pbpTable, sizeof(TBattlePassRanking) * dwCount);
		return;
	}
	else
	{
		static std::vector<TBattlePassRanking> sendVector;
		sendVector.resize(m_vec_battlePassRanking.size());
	
		MYSQL_ROW row;
	
		for (int i = 0; i < m_vec_battlePassRanking.size(); ++i)
		{
			TBattlePassRanking * pkRanking = m_vec_battlePassRanking[i];
			TBattlePassRanking & r = sendVector[i];

			r.bPos = pkRanking->bPos;
			strlcpy(r.playerName, pkRanking->playerName, sizeof(r.playerName));
			r.dwFinishTime = pkRanking->dwFinishTime;
		}
	
		sys_log(0, "RequestLoadBattlePassRanking: count %d PID %u", sendVector.size(), dwPlayerID);
	
		DWORD dwCount = sendVector.size();
	
		peer->EncodeHeader(HEADER_DG_BATTLE_PASS_LOAD_RANKING, dwHandle, sizeof(DWORD) + sizeof(BYTE) + sizeof(DWORD) + sizeof(TBattlePassRanking) * dwCount);
		peer->Encode(&dwPlayerID, sizeof(DWORD));
		peer->Encode(&bIsGlobal, sizeof(BYTE));
		peer->Encode(&dwCount, sizeof(DWORD));
		peer->Encode(&sendVector[0], sizeof(TBattlePassRanking) * dwCount);
	}
}

void CClientManager::QUERY_REGISTER_RANKING(CPeer * peer, DWORD dwHandle, TBattlePassRegisterRanking* pRanking)
{
	if (g_test_server)
		sys_log(0, "REGISTER_RANKING: %s id %d", pRanking->playerName, pRanking->bBattlePassId);

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery),
		"REPLACE INTO battle_pass_ranking (player_name, battle_pass_id, finish_time) VALUES ('%s', %d, NOW())", pRanking->playerName, pRanking->bBattlePassId);
		
	CDBManager::instance().AsyncQuery(szQuery);
}
#endif