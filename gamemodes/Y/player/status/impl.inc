#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

loadtext y_players[status];

hook OnGroupInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:stats;
	}
}

hook OnPlayerLogin(playerid)
{
	#if defined Y_PLAYER_REQUIRE_ACCOUNT
		inline FetchedPlayerStatus()
		{
			if (!cache_num_rows()) {
				@return log("Did not find player %d status data", playerid);
			}

			cache_get_value_name_int(0, "vip", Player.Status[playerid][@vip]);
			cache_get_value_name_int(0, "money", Player.Status[playerid][@money]);
			
			new admin = 0;
			cache_get_value_name_int(0, "admin", admin);
			Player.Status[playerid][@admin] = admin;

			if (admin > 0) {
				Group_SetPlayer(AdminGroup[admin - 1], playerid, true);
			}

			new dev = 0;
			cache_get_value_name_int(0, "developer", dev);
			Player.Status[playerid][@developer] = !!dev;

			if (Player.Status[playerid][@developer]) {
				Group_SetPlayer(DeveloperGroup, playerid, true);
			}

			@return log("Loaded player %d status data", playerid);
		}

		new query[80];
		mysql_format(dbhandle, query, sizeof query, "SELECT * FROM player_statuses WHERE player_id = %d LIMIT 1", _:Player.Auth[playerid][@id]);
		mysql_tquery_inline(dbhandle, query, using inline FetchedPlayerStatus);
	#endif

	new ip[16];
	GetPlayerIp(playerid, ip, sizeof ip);
	Player.Status[playerid][@ip] = IPToInt(ip);

	return 1;
}

#if defined Y_PLAYER_REQUIRE_ACCOUNT
	hook OnPlayerRegister(playerid)
	{
		new query[128];
		mysql_format(dbhandle, query, sizeof query, "INSERT INTO player_statuses(player_id) VALUES(%d)", _:Player.Auth[playerid][@id]);
		mysql_pquery(dbhandle, query);

		return 1;
	}
#endif

hook OnPlayerStats(playerid)
{
	Text_Send(playerid, $PLAYER_STATS, Player.Status[playerid][@money], Player.Status[playerid][@developer] ? "Yes" : "No", Player.Status[playerid][@vip] ? "Yes" : "No", Player.Status[playerid][@admin]);

	return 1;	
}

hook OnPlayerDisconnect(playerid, reason)
{
	memset(PlayerStatus[playerid][E_PLAYER_STATUS:0], _:E_PLAYER_STATUS, 0);

	return 1;
}

YCMD:stats(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	call OnPlayerStats(playerid);

	return 1;
}