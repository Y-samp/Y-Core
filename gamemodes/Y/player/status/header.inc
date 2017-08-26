#if defined _inc_header
	#undef _inc_header
#endif

enum E_PLAYER_STATUS {
	E_PLAYER_Status_money,
	E_PLAYER_Status_vip,
	bool:E_PLAYER_Status_developer
}

new PlayerStatus[MAX_PLAYERS][E_PLAYER_STATUS];