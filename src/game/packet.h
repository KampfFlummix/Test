/* 
packet.h

Suchen "enum CG_HEADERS"

danach 	
	// HEADER_CG_UNUSED = 238,

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	HEADER_CG_BATTLE_PASS = 239,
#endif



/*
Suchen "enum GC_HEADERS"

danach 	
	// HEADER_GC_UNUSED = 234,

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	HEADER_GC_BATTLE_PASS_OPEN = 235,
	HEADER_GC_BATTLE_PASS_UPDATE = 236,
	HEADER_GC_BATTLE_PASS_RANKING = 237,
#endif



/*
am Ende

vor 	
#pragma pack()
#endif

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
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