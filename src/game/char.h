/* 
char.h

Suchen "enum EPointTypes"

am Ende

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	POINT_BATTLE_PASS_ID,
#endif


/*
am Ende vor : 
"
};

ESex GET_SEX(LPCHARACTER ch);

#endif
"

hinzufügen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	typedef std::list<TPlayerBattlePassMission*> ListBattlePassMap;
public:
	void LoadBattlePass(DWORD dwCount, TPlayerBattlePassMission* data);
	DWORD GetMissionProgress(DWORD dwMissionID, DWORD dwBattlePassID);
	void UpdateMissionProgress(DWORD dwMissionID, DWORD dwBattlePassID, DWORD dwUpdateValue, DWORD dwTotalValue, bool isOverride = false);
	bool IsCompletedMission(BYTE bMissionType);
	bool IsLoadedBattlePass() const { return m_bIsLoadedBattlePass; }
	BYTE GetBattlePassId();
private:
	bool m_bIsLoadedBattlePass;
	ListBattlePassMap m_listBattlePass;
#endif

#ifdef __BATTLE_PASS_SYSTEM__
public:
	int 			GetSecondsTillNextMonth();
	int 			GetBattlePassEndTime() { return (m_dwBattlePassEndTime - get_global_time()); };
protected:
	DWORD			m_dwBattlePassEndTime;
#endif

