#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_text>
#include <YSI\y_inline>
#include <YSI\y_groups>

enum E_PLAYER_AUTH {
	DBID:E_PLAYER_Auth_id,
	E_PLAYER_Auth_name[MAX_PLAYER_NAME + 1],
	E_PLAYER_Auth_password[64 + 1],
	E_PLAYER_Auth_salt[64 + 1]
}

new PlayerAuth[MAX_PLAYERS][E_PLAYER_AUTH];

new
	Group:LoggedGroup
;