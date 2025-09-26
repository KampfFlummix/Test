/* 
packet_info_ws.cpp

Suchen "CPacketInfoCG::CPacketInfoCG()"

vor 	
CPacketInfoCG::~CPacketInfoCG()

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	Set(HEADER_CG_BATTLE_PASS, sizeof(TPacketCGBattlePassAction), "BattlePass", true);
#endif