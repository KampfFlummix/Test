//tables.h
// Suchen "enum GD_HEADERS" hinzufügen : 



#ifdef __BATTLE_PASS_SYSTEM__
	HEADER_GD_SAVE_BATTLE_PASS = 147,
	HEADER_GD_REGISTER_BP_RANKING = 148,
	HEADER_GD_BATTLE_PASS_RANKING = 149,
#endif



// Suchen "enum DG_HEADERS" hinzufügen : 

#ifdef __BATTLE_PASS_SYSTEM__
	HEADER_DG_BATTLE_PASS_LOAD = 187,
	HEADER_DG_BATTLE_PASS_LOAD_RANKING = 188,
#endif


// Suchen "typedef struct SPlayerTable" hinzufügen : 
// avant : 
// } TPlayerTable;
// ajoute

#ifdef __BATTLE_PASS_SYSTEM__
	DWORD	dwBattlePassEndTime;
#endif



// A la fin et avant "#pragma pack()" hinzufügen : 

#ifdef __BATTLE_PASS_SYSTEM__
typedef struct SPlayerBattlePassMission
{
	DWORD dwPlayerId;
	DWORD dwMissionId;
	DWORD dwBattlePassId;
	DWORD dwExtraInfo;
	BYTE bCompleted;
	BYTE bIsUpdated;
} TPlayerBattlePassMission;

typedef struct SBattlePassRewardItem
{
	DWORD dwVnum;
	BYTE bCount;
} TBattlePassRewardItem;

typedef struct SBattlePassMissionInfo
{
	BYTE bMissionType;
	DWORD dwMissionInfo[3];
	TBattlePassRewardItem aRewardList[MISSION_REWARD_COUNT];
} TBattlePassMissionInfo;

typedef struct SBattlePassRanking
{
	BYTE bPos;
	char playerName[CHARACTER_NAME_MAX_LEN + 1];
	DWORD dwFinishTime;
} TBattlePassRanking;

typedef struct SBattlePassRegisterRanking
{
	BYTE bBattlePassId;
	char playerName[CHARACTER_NAME_MAX_LEN + 1];
} TBattlePassRegisterRanking;
#endif