/* 
main.cpp

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
#include "battle_pass.h"
#endif




/*
Suchen "int main(int argc, char** argv)"

danach 	
	CSpeedServerManager SSManager;
	DSManager dsManager

hinzuf�gen : 
*/

#ifdef __BATTLE_PASS_SYSTEM__
	CBattlePass battle_pass;
#endif