#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_text>
#include <YSI\y_hooks>

loadtext y_players[auth];

hook OnPlayerConnect(playerid)
{
	if (funcidx(Y_PLAYER_RESTRICT_NAME_FUNC) != -1) {
		new ret = CallLocalFunction(Y_PLAYER_RESTRICT_NAME_FUNC, "i", playerid);

		if(ret != 1) {
			return 1;
		}
	}

	#if defined Y_PLAYER_REQUIRE_ACCOUNT	
		FetchPlayer(playerid);
	#else
		call OnPlayerLogin(playerid);
	#endif

	return 1;
}

hook OnPlayerLogin(playerid)
{
	Group_SetPlayer(LoggedGroup, playerid, true);
	SpawnPlayer(playerid);

	return 1;
}

hook OnGameModeInit()
{
	DeveloperGroup = Group_Create("Developer");

	return 1;
}

#if defined Y_PLAYER_REQUIRE_ACCOUNT
hook OnPlayerRequestClass(playerid, classid)
{
	SetSpawnInfo(playerid, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, true);

	return 1;
}

hook OnPlayerSpawn(playerid)
{
	TogglePlayerSpectating(playerid, false);

	return 1;
}

FetchPlayer(playerid)
{
	new query[64 + MAX_PLAYER_NAME + 1];
	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof name);

	strcpy(Player.Auth[playerid][name], name);

	mysql_format(dbhandle, query, sizeof query, "SELECT id, password, salt FROM players WHERE name = '%e'", name);

	inline PlayerFetched()
	{
		if (cache_num_rows()) {
			cache_get_value_name_int(0, "id", _:Player.Auth[playerid][id]);
			cache_get_value_name(0, "password", Player.Auth[playerid][password]);
			cache_get_value_name(0, "salt", Player.Auth[playerid][salt]);
			@return ShowLoginDialog(playerid);
		}

		#if defined Y_PLAYER_REGISTRATION
			@return ShowRegistrationDialog(playerid);
		#else
			Text_Send(playerid, $REGISTRAION_VIA_WEBSITE);
			defer TimedKick(playerid);
			@return 1;
		#endif
	}

	mysql_tquery_inline(dbhandle, query, using inline PlayerFetched);

}
#endif

YCMD:enter(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	call OnPlayerEnter(playerid);	

	return 1;
}