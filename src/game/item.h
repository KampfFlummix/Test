/* 
item.h

Suchen "class CItem : public CEntity /> public"

danach 	
DWORD GetLastOwnerPID() { return m_dwLastOwnerPID; }

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	bool HaveOwnership() { return (m_pkOwnershipEvent ? true : false); }
#endif