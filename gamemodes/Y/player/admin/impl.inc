#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

loadtext y[core], y_players[admin];

hook OnGameModeInit()
{
	CreateAdminGroups();

	Command_AddAlt(YCMD:setadminlevel, "sal");
}

hook OnGroupInit()
{
	Group_AddChild(AdminGroup[0], DeveloperGroup);

	GROUP_ADD<AdminGroup[Y_PLAYER_ADMIN_MAX_LEVEL - 1]>
	{
		@YCMD:setadminlevel;
		@YCMD:sal;
	}

	return 1;
}

// http://forum.sa-mp.com/showpost.php?p=2894606&postcount=3
hook OnRconLoginAttempt(ip[], password[], success)
{
	if (success) {
		defer RetrieveRconPlayer(ip);
	}

	return 1;
}

hook OnPlayerRconLogin(playerid)
{
	SetAdminLevel(playerid, Y_PLAYER_ADMIN_MAX_LEVEL, true);

	return 1;
}

timer RetrieveRconPlayer[1000](string:ip[])
{
	new ip2 = IPToInt(ip);

	foreach(new player:Player) {
		if (Player.Status[player][ip] == ip2 && IsPlayerAdmin(player)) {
			CallRemoteFunction("OnPlayerRconLogin", "i", player);

			return 1;
		}
	}

	return 1;
}

CreateAdminGroups()
{
	for (new i = 0; i != Y_PLAYER_ADMIN_MAX_LEVEL; ++i) {
		new name[32];
		format(name, sizeof name, "Admin level %d", i + 1);
		AdminGroup[i] = Group_Create(name);
		if (i > 0) {
			Group_AddChild(AdminGroup[i], AdminGroup[i - 1]);
		}
	}
}

ClearAdminLevel(playerid)
{
	if (Player.Status[playerid][admin] > 0) {
		Group_SetPlayer(AdminGroup[Player.Status[playerid][admin] - 1], playerid, false);	
	}
}

SetAdminLevel(playerid, level, bool:force = false)
{
	if (!force && IsPlayerAdmin(playerid)) {
		return 2;
	}

	ClearAdminLevel(playerid);

	if (!(1 <= level <= Y_PLAYER_ADMIN_MAX_LEVEL)) {
		printf("Player %d admin level cannot be set to %d", playerid, level);

		return 1;
	}

	Group_SetPlayer(AdminGroup[level - 1], playerid, true);
	Player.Status[playerid][admin] = level;

	return 0;
}

bool:IsAdminLevel(playerid, level)
{
	if (IsPlayerAdmin(playerid)) {
		return true;
	}

	if (1 <= level <= Y_PLAYER_ADMIN_MAX_LEVEL) {
		return Group_GetPlayer(AdminGroup[level - 1], playerid);
	}

	return false;
}

YCMD:setadminlevel(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	new
		targetid,
		level,
		announce
	;

	if (sscanf(params, "udD(0)", targetid, level, announce)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_SAL, YCMD:sal);
	if (targetid == playerid) return Text_Send(playerid, $CANNOT_USE_ON_SELF);
	if (!IsPlayerConnected(targetid)) return Text_Send(playerid, $INVALID_PLAYER_SPECIFIED);
	if (Player.Status[playerid][admin] <= Player.Status[targetid][admin]) return Text_Send(playerid, $UNAUTHORIZED_ACTION);

	new sal = SetAdminLevel(targetid, level);
	if(sal) {
		if (sal == 1) return Text_Send(playerid, $INVALID_LEVEL_SPECIFIED, 1, Y_PLAYER_ADMIN_MAX_LEVEL);
		else if (sal == 2) return Text_Send(playerid, $UNAUTHORIZED_ACTION);
	}

	Text_Send(playerid, $ACTION_SUCCESS);
	Text_Send(AdminGroup[0], $ADMIN_LEVEL_CHANGE, Player.Auth[targetid][name], level, Player.Auth[playerid][name]);
	
	if (announce) {
		Text_Send(LoggedGroup, $ADMIN_LEVEL_CHANGE, Player.Auth[targetid][name], level, Player.Auth[playerid][name]);
	}

	#if defined Y_PLAYER_REQUIRE_ACCOUNT
		new query[80];
		mysql_format(dbhandle, query, sizeof query, "UPDATE player_statuses SET admin = %d WHERE player_id = %d", Player.Status[targetid][admin], _:Player.Auth[targetid][id]);
		mysql_pquery(dbhandle, query);
	#endif

	return 1;
}