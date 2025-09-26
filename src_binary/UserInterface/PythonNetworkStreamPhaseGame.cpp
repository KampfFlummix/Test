/* 
PythonNetworkStreamPhaseGame.cpp

Suchen "switch (header)"

danach 	
		case HEADER_GC_DRAGON_SOUL_REFINE:
			ret = RecvDragonSoulRefine();
			break;

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
		case HEADER_GC_BATTLE_PASS_OPEN:
			ret = RecvBattlePassPacket();
			break;

		case HEADER_GC_BATTLE_PASS_UPDATE:
			ret = RecvBattlePassUpdatePacket();
			break;

		case HEADER_GC_BATTLE_PASS_RANKING:
			ret = RecvBattlePassRankingPacket();
			break;
#endif


/*
am Ende

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
bool CPythonNetworkStream::SendBattlePassAction(BYTE bAction)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGBattlePassAction packet;
	packet.bHeader = HEADER_CG_BATTLE_PASS;
	packet.bAction = bAction;

	if (!Send(sizeof(TPacketCGBattlePassAction), &packet))
	{
		Tracef("SendBattlePassAction Send Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::RecvBattlePassPacket()
{
	TPacketGCBattlePass packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	// PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassClearMission", Py_BuildValue("()"));

	packet.wSize -= sizeof(packet);
	while (packet.wSize > 0)
	{
		TBattlePassMissionInfo missionInfo;
		if (!Recv(sizeof(missionInfo), &missionInfo))
			return false;

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassAddMission", Py_BuildValue("(iiii)",
			missionInfo.bMissionType, missionInfo.dwMissionInfo[0], missionInfo.dwMissionInfo[1], missionInfo.dwMissionInfo[2]));

		for (int i = 0; i < 3; ++i)
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassAddMissionReward", Py_BuildValue("(iii)",
				missionInfo.bMissionType, missionInfo.aRewardList[i].dwVnum, missionInfo.aRewardList[i].bCount));

		packet.wSize -= sizeof(missionInfo);
	}

	while (packet.wRewardSize > 0)
	{
		TBattlePassRewardItem rewardInfo;
		if (!Recv(sizeof(rewardInfo), &rewardInfo))
			return false;

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassAddReward", Py_BuildValue("(ii)", rewardInfo.dwVnum, rewardInfo.bCount));

		packet.wRewardSize -= sizeof(rewardInfo);
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassOpen", Py_BuildValue("()"));

	return true;
}

bool CPythonNetworkStream::RecvBattlePassRankingPacket()
{
	TPacketGCBattlePassRanking packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	packet.wSize -= sizeof(packet);
	while (packet.wSize > 0)
	{
		TBattlePassRanking rankingInfo;
		if (!Recv(sizeof(rankingInfo), &rankingInfo))
			return false;

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassAddRanking", Py_BuildValue("(isi)",
			rankingInfo.bPos, rankingInfo.playerName, rankingInfo.dwFinishTime));

		packet.wSize -= sizeof(rankingInfo);
	}

	if (packet.bIsGlobal)
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassOpenRanking", Py_BuildValue("()"));
	else
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassRefreshRanking", Py_BuildValue("()"));

	return true;
}

bool CPythonNetworkStream::RecvBattlePassUpdatePacket()
{
	TPacketGCBattlePassUpdate packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BattlePassUpdate", Py_BuildValue("(ii)", packet.bMissionType, packet.dwNewProgress));

	return true;
}
#endif