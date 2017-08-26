#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

loadtext y_players[auth];

hook OnPlayerRegister(playerid)
{
	printf("Player %d registered", playerid);
	#if defined Y_PLAYER_LOGIN_AFTER_REG
	call OnPlayerLogin(playerid);
	#else
	FetchPlayer(playerid);
	#endif

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
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_SHORT, Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH);
			}
			case e_ERROR_PASSWORD_LONG: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_LONG, Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH);
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

	Text_PasswordBox(playerid, using inline HandleRegistration, $REGISTRATION_BOX_TITLE, $REGISTRATION_BOX_TEXT, $REGISTRATION_BOX_REGISTER, $REGISTRATION_BOX_EXIT, error, Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH, Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH);

	return 1;
}

CheckRegistrationPassword(playerid, password[])
{
	new len = strlen(password);

	if (isnull(password)) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_EMPTY);
	}

	if (len < Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_SHORT);
	}

	if (len > Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_LONG);
	}

	return Register(playerid, password);
}

Register(playerid, const password[])
{
	new
		salt[32 + 1],
		peppered[128 + Y_PLAYER_PEPPER_SIZE + 1],
		hash[64 + 1]
	;
	GenerateSalt(salt);

	strcpy(peppered, Y_PLAYER_PASSWORD_PEPPER);
	strcat(peppered, password);

	SHA256_PassHash(peppered, salt, hash, sizeof hash);

	strcpy(Player.Auth[playerid][salt], salt);
	strcpy(Player.Auth[playerid][password], hash);

	new
		query[256]
	;

	mysql_format(dbhandle, query, sizeof query, "INSERT INTO players VALUES (null, '%e', '%e', '%e', NOW())", Player.Auth[playerid][name], Player.Auth[playerid][password], Player.Auth[playerid][salt]);

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