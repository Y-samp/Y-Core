loadtext y_players[auth];

new
	Timer:inactivityKick[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{
	if (funcidx(Y_PLAYER_RESTRICT_FUNC_NAME) != -1) {
		if(CallLocalFunction(Y_PLAYER_RESTRICT_FUNC_NAME, "i", playerid) != 1) {
			return 1;
		}
	}

	FetchPlayer(playerid);

	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	stop inactivityKick[playerid];

	return 1;
}

hook OnPlayerLogin(playerid)
{
	printf("Player %d logged in", playerid);
}

hook OnPlayerRegister(playerid)
{
	printf("Player %d registered", playerid);
	FetchPlayer(playerid);
}

hook OnPlayerRequestClass(playerid, classid)
{
    SetSpawnInfo(playerid, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, true);

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

FetchPlayer(playerid)
{
	new query[40 + MAX_PLAYER_NAME + 1];
	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof name);

	strcpy(Player.Meta[playerid][name], name);

	mysql_format(dbhandle, query, sizeof query, "SELECT * FROM players WHERE name = '%e'", name);

	inline PlayerFetched()
	{
		if (cache_num_rows()) {
			cache_get_value_name(0, "password", Player.Meta[playerid][password]);
			cache_get_value_name(0, "salt", Player.Meta[playerid][salt]);
			@return ShowLoginDialog(playerid);
		}

		#if defined Y_USER_REGISTRATION
			@return ShowRegistrationDialog(playerid);
		#else
			Text_Send(playerid, $REGISTRAION_VIA_WEBSITE);
			defer TimedKick(playerid);
			@return 1;
		#endif
	}

	mysql_tquery_inline(dbhandle, query, using inline PlayerFetched);

}

ShowLoginDialog(playerid, attempt = 1)
{
	new
		error[32]
	;

	inactivityKick[playerid] = repeat KickOnInactivity[Y_USER_LOGIN_TIMEOUT_KICK * 1000](playerid);

	if (attempt > 1) {
		Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $INVALID_PASSWORD);
	}

	if (attempt >= Y_USER_LOGIN_MAX_ATTEMPTS) {
		Text_Send(playerid, $EXCEEDED_MAX_LOGIN_ATTEMPTS, Y_USER_LOGIN_MAX_ATTEMPTS);
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

	Text_PasswordBox(playerid, using inline HandleLogin, $LOGIN_BOX_TITLE, $LOGIN_BOX_TEXT, $LOGIN_BOX_LOGIN, $LOGIN_BOX_EXIT, error, attempt, Y_USER_LOGIN_MAX_ATTEMPTS);

	return 1;
}

ShowRegistrationDialog(playerid, e_ERROR_PASSWORD:errorCode = e_ERROR_PASSWORD_NONE)
{
	new
		error[64]
	;

	if (errorCode != e_ERROR_PASSWORD_NONE) {
		switch (errorCode) {
			case e_ERROR_PASSWORD_EMPTY: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_EMPTY);
			}
			case e_ERROR_PASSWORD_SHORT: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_SHORT, Y_USER_REGISTRATION_MIN_PASS_LENGTH);
			}
			case e_ERROR_PASSWORD_LONG: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_LONG, Y_USER_REGISTRATION_MAX_PASS_LENGTH);
			}
		}
	}

	inline HandleRegistration(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem

		if (!response) {
			defer TimedKick(playerid);
			@return 1;
		}

		CheckRegistrationPassword(playerid, inputtext);
	}

	Text_PasswordBox(playerid, using inline HandleRegistration, $REGISTRATION_BOX_TITLE, $REGISTRATION_BOX_TEXT, $REGISTRATION_BOX_REGISTER, $REGISTRATION_BOX_EXIT, error, Y_USER_REGISTRATION_MIN_PASS_LENGTH, Y_USER_REGISTRATION_MAX_PASS_LENGTH);

	return 1;
}

CheckUserPassword(playerid, const password[])
{
	new
		peppered[128 + Y_USER_PEPPERED_SIZE + 1],
		hash[64 + 1]
	;

	strcpy(peppered, Y_USER_PASSWORD_PEPPER);
	strcat(peppered, password);

	SHA256_PassHash(peppered, Player.Meta[playerid][salt], hash, sizeof hash);

	if (!strcmp(hash, Player.Meta[playerid][password])) return true;

	return false;
}

CheckRegistrationPassword(playerid, password[])
{
	new len = strlen(password);

	if (isnull(password)) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_EMPTY);
	}

	if (len < Y_USER_REGISTRATION_MIN_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_SHORT);
	}

	if (len > Y_USER_REGISTRATION_MAX_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_LONG);
	}

	return Register(playerid, password);
}

Register(playerid, const password[])
{
	new
		salt[32 + 1],
		peppered[128 + Y_USER_PEPPERED_SIZE + 1],
		hash[64 + 1]
	;
	GenerateSalt(salt);

	strcpy(peppered, Y_USER_PASSWORD_PEPPER);
	strcat(peppered, password);

	SHA256_PassHash(peppered, salt, hash, sizeof hash);

	strcpy(Player.Meta[playerid][salt], salt);
	strcpy(Player.Meta[playerid][password], hash);

	new
		query[256]
	;

	mysql_format(dbhandle, query, sizeof query, "INSERT INTO players VALUES (null, '%e', '%e', '%e', NOW())", Player.Meta[playerid][name], Player.Meta[playerid][password], Player.Meta[playerid][salt]);

	inline SavePlayer()
	{
		call OnPlayerRegister(playerid);
	}

	mysql_tquery_inline(dbhandle, query, using inline SavePlayer);

	return 1;
}
	
GenerateSalt(dest[], size = sizeof dest)
{
	randomString(dest, size - 1);
}