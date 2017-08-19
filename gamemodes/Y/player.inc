#if defined _INC_player
	#endinput
#endif
#define _INC_player

#include "player/header"
#if defined Y_PLAYER_REQUIRE_ACCOUNT
	#include "player/login"
	#include "player/registration"
#endif
#include "player/impl"

#if defined RUN_TESTS
	#include <YSI\y_testing>
	#include "player/tests"
#endif