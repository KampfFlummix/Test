/* 
PythonNetworkStream.h

danach 	
	BOOL IsGameOnline();
	
hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
public:
	bool SendBattlePassAction(BYTE bAction);

protected:
	bool RecvBattlePassPacket();
	bool RecvBattlePassRankingPacket();
	bool RecvBattlePassUpdatePacket();
#endif
