/* 
GameType.h

Suchen "typedef struct packet_item"

davor
#pragma pack(pop)

inline float GetSqrtDistance(int ix1, int iy1, int ix2, int iy2) // By sqrt

hinzufügen : 
*/

#ifdef ENABLE_BATTLE_PASS_SYSTEM
typedef struct SBattlePassRewardItem
{
	DWORD dwVnum;
	BYTE bCount;
} TBattlePassRewardItem;

typedef struct SBattlePassMissionInfo
{
	BYTE bMissionType;
	DWORD dwMissionInfo[3];
	TBattlePassRewardItem aRewardList[3];
} TBattlePassMissionInfo;

typedef struct SBattlePassRanking
{
	BYTE bPos;
	char playerName[24 + 1];
	DWORD dwFinishTime;
} TBattlePassRanking;
#endif
