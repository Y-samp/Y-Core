#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_commands>
#include <YSI\y_utils>

enum E_PLAYER_STATUS {
	E_PLAYER_Status_ip,
	E_PLAYER_Status_money,
	E_PLAYER_Status_vip,
	E_PLAYER_Status_admin,
	bool:E_PLAYER_Status_developer
}

new PlayerStatus[MAX_PLAYERS][E_PLAYER_STATUS];