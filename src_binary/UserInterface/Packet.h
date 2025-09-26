/* 
Packet.h

danach 	
// HEADER_CG_UNUSED = 238,

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
	HEADER_CG_BATTLE_PASS = 239,
#endif



/*
danach 	
// HEADER_GC_UNUSED = 234,

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
	HEADER_GC_BATTLE_PASS_OPEN = 235,
	HEADER_GC_BATTLE_PASS_UPDATE = 236,
	HEADER_GC_BATTLE_PASS_RANKING = 237,
#endif



/*
Suchen "enum EPointTypes"

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
	POINT_BATTLE_PASS_ID = 192,			// 192
#endif



/*
am Ended

davor: 
#pragma pack(pop)

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
typedef struct SPacketGCBattlePass
{
	BYTE bHeader;
	WORD wSize;
	WORD wRewardSize;
} TPacketGCBattlePass;

typedef struct SPacketGCBattlePassUpdate
{
	BYTE bHeader;
	BYTE bMissionType;
	DWORD dwNewProgress;
} TPacketGCBattlePassUpdate;

typedef struct SPacketCGBattlePassAction
{
	BYTE bHeader;
	BYTE bAction;
} TPacketCGBattlePassAction;

typedef struct SPacketGCBattlePassRanking
{
	BYTE bHeader;
	WORD wSize;
	BYTE bIsGlobal;
} TPacketGCBattlePassRanking;
#endif