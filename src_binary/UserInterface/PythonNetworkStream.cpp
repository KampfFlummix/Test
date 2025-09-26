/* 
PythonNetworkStream.cpp

Suchen "public:
	CMainPacketHeaderMap()"

davor 	
};

int g_iLastPacket[2] = { 0, 0 };

void CPythonNetworkStream::ExitApplication()

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
		Set(HEADER_GC_BATTLE_PASS_OPEN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBattlePass), DYNAMIC_SIZE_PACKET));
		Set(HEADER_GC_BATTLE_PASS_UPDATE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBattlePassUpdate), STATIC_SIZE_PACKET));
		Set(HEADER_GC_BATTLE_PASS_RANKING, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBattlePassRanking), DYNAMIC_SIZE_PACKET));
#endif
