#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:stats;
	}
}

hook OnPlayerLogin(playerid)
{
	inline FetchedPlayerStatus()
	{
		if (!cache_num_rows()) {
			@return log("Did not find player status data");
		}

		cache_get_value_name_int(0, "vip", Player.Status[playerid][vip]);
		cache_get_value_name_int(0, "money", Player.Status[playerid][money]);
		
		new admin = 0;
		cache_get_value_name_int(0, "admin", admin);
		Player.Status[playerid][admin] = admin;

		if (admin > 0) {
			Group_SetPlayer(AdminGroup[admin - 1], playerid, true);
		}

		new dev = 0;
		cache_get_value_name_int(0, "developer", dev);
		Player.Status[playerid][developer] = !!dev;

		if (Player.Status[playerid][developer]) {
			Group_SetPlayer(DeveloperGroup, playerid, true);
		}

		@return log("Loaded player %d status data", playerid);
	}

	new query[80];
	mysql_format(dbhandle, query, sizeof query, "SELECT * FROM player_statuses WHERE player_id = %d LIMIT 1", _:Player.Auth[playerid][id]);
	mysql_tquery_inline(dbhandle, query, using inline FetchedPlayerStatus);

	new ip[16];
	GetPlayerIp(playerid, ip, sizeof ip);
	Player.Status[playerid][ip] = IPToInt(ip);

	return 1;
}

hook OnPlayerStats(playerid)
{
	new str[144];
	format(str, sizeof str, "[Money]: %d ", Player.Status[playerid][money]);
	format(str, sizeof str, "%s[Developer]: %s ", str, Player.Status[playerid][developer] ? "Yes" : "No");
	format(str, sizeof str, "%s[Vip]: %s ", str, Player.Status[playerid][vip] ? "Yes" : "No");
	format(str, sizeof str, "%s[Admin level]: %d", str, Player.Status[playerid][admin]);

	SCM(playerid, -1, str);

	return 1;	
}

YCMD:stats(playerid, params[], help)
{
    if(help) return SCM(playerid, -1, "Not supported");

    call OnPlayerStats(playerid);

    return 1;
}