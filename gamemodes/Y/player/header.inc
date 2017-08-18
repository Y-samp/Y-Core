#include "utils"
#include <YSI\y_dialog>
#include <YSI\y_text>
#include <YSI\y_hooks>
#include <YSI\y_dialog>
#include <YSI\y_va>
#include <YSI\y_inline>
#include <YSI\y_text>

#define Y_PLAYER_RESTRICT_FUNC_NAME "PlayerRestrictName"

#define Player.%0[%1][%2] Player%0[%1][E_PLAYER_%0_%2]

enum E_PLAYER_META {
	DBID:E_PLAYER_Meta_id,
	E_PLAYER_Meta_name[MAX_PLAYER_NAME + 1],
	E_PLAYER_Meta_password[64 + 1],
	E_PLAYER_Meta_salt[64 + 1]
}

new PlayerMeta[MAX_PLAYERS][E_PLAYER_META];

enum e_ERROR_PASSWORD {
	e_ERROR_PASSWORD_NONE,
	e_ERROR_PASSWORD_EMPTY,
	e_ERROR_PASSWORD_SHORT,
	e_ERROR_PASSWORD_LONG
}

#define SALT_NONE						0
#define SALT_WEAK					 	1
#define SALT_REMOTE_STRONG 	2

#if !defined Y_USER_SALT_GENERATOR
	#define Y_USER_SALT_GENERATOR SALT_WEAK
#endif