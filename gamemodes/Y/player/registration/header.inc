#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_dialog>
#include <YSI\y_text>
#include <YSI\y_inline>

enum e_ERROR_PASSWORD {
	e_ERROR_PASSWORD_NONE,
	e_ERROR_PASSWORD_EMPTY,
	e_ERROR_PASSWORD_SHORT,
	e_ERROR_PASSWORD_LONG
}

enum e_SALT {
	SALT_NONE,
	SALT_WEAK,
	SALT_REMOTE_STRONG
}

#if !defined Y_PLAYER_SALT_GENERATOR
	#define Y_PLAYER_SALT_GENERATOR SALT_WEAK
#endif

#define ALS_DO_PlayerRegister<%0> %0<PlayerRegister,i>(end:playerid)
