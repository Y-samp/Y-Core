#include <a_samp>
#include <fixes>

#define _DEBUG 7
// #define RUN_TESTS

#if defined RUN_TESTS
	#include <YSI\y_testing>
#endif

#include "config"
#include "Y\log"
#include "Y\db"

#include "Y\player"

new
	Language:LangEN = NO_LANGUAGE
;

main () {
	print("====== Y-Core ======");
}

public OnGameModeInit()
{
	LangEN = Langs_Add("EN", "English");

	return 1;
}

public OnPlayerConnect(playerid)
{
	Langs_SetPlayerLanguage(playerid, LangEN);

	return 1;
}