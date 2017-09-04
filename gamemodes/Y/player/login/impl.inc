#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

loadtext y_players[auth];

static
	Timer:inactivityKick[MAX_PLAYERS]
;

hook OnPlayerDisconnect(playerid, reason)
{
	stop inactivityKick[playerid];

	return 1;
}

hook OnPlayerLogin(playerid)
{
	printf("Player %d logged in", playerid);
	ClearPlayerMeta(playerid);

	return 1;
}

timer KickOnInactivity[30000](playerid)
{
	Text_Send(playerid, $INACTIVE_KICK);
	defer TimedKick(playerid);
}

timer LoginNextAttempt[500](playerid, attempt)
{
	ShowLoginDialog(playerid, attempt);
}

ShowLoginDialog(playerid, attempt = 1)
{
	new
		error[32]
	;

	inactivityKick[playerid] = repeat KickOnInactivity[Y_PLAYER_LOGIN_TIMEOUT_KICK * 1000](playerid);

	if (attempt > 1) {
		Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $INVALID_PASSWORD);
	}

	if (attempt >= Y_PLAYER_LOGIN_MAX_ATTEMPTS) {
		Text_Send(playerid, $EXCEEDED_MAX_LOGIN_ATTEMPTS, Y_PLAYER_LOGIN_MAX_ATTEMPTS);
		defer TimedKick(playerid);
	}

	inline HandleLogin(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem

		stop inactivityKick[playerid];

		if (!response) {
			defer TimedKick(playerid);
			@return 1;
		}

		if (CheckUserPassword(playerid, inputtext)) {
			call OnPlayerLogin(playerid);
		} else {
			defer LoginNextAttempt[500](playerid, attempt + 1);
		}
	}

	Text_PasswordBox(playerid, using inline HandleLogin, $LOGIN_BOX_TITLE, $LOGIN_BOX_TEXT, $LOGIN_BOX_LOGIN, $LOGIN_BOX_EXIT, error, attempt, Y_PLAYER_LOGIN_MAX_ATTEMPTS);

	return 1;
}

CheckUserPassword(playerid, const password[])
{
	new
		peppered[128 + Y_PLAYER_PEPPER_SIZE + 1],
		hash[64 + 1]
	;

	strcpy(peppered, Y_PLAYER_PASSWORD_PEPPER);
	strcat(peppered, password);

	SHA256_PassHash(peppered, Player.Auth[playerid][@salt], hash, sizeof hash);

	if (!strcmp(hash, Player.Auth[playerid][@password])) return true;

	return false;
}

ClearPlayerMeta(playerid)
{
	memset(PlayerAuth[playerid][E_PLAYER_Auth_password], 0);
	memset(PlayerAuth[playerid][E_PLAYER_Auth_salt], 0);
}