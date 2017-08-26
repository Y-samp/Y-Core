#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnPlayerLogin(playerid)
{
	inline FetchedPlayerStatus()
	{
		if (!cache_num_rows()) {
			@return log("Did not find player status data");
		}

		cache_get_value_name_int(0, "vip", Player.Status[playerid][vip]);
		cache_get_value_name_int(0, "money", Player.Status[playerid][money]);
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

	return 1;
}