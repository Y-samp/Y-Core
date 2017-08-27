#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	CreateAdminGroups();

	GROUP_ADD<AdminGroup[0]>
	{
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
	Group_SetPlayer(AdminGroup[sizeof(AdminGroup) - 1], playerid, true);

	return 1;
}

timer RetrieveRconPlayer[1000](string:ip[])
{
	new ip2 = IPToInt(ip);

	foreach(new player:Player) {
		if (Player.Status[player][ip] == ip2 && IsPlayerAdmin(player)) {
			CallRemoteFunction("OnPlayerRconLogin", "i", player);
		}
	}

	return 1;
}

CreateAdminGroups()
{
	for (new i = 0; i != sizeof AdminGroup; ++i) {
		new name[32];
		format(name, sizeof name, "Admin level %d", i + 1);
		AdminGroup[i] = Group_Create(name);
		if (i > 0) {
			Group_AddChild(AdminGroup[i], AdminGroup[i - 1]);
		}
	}
}

bool:IsAdminLevel(playerid, level)
{
	if (IsPlayerAdmin(playerid)) {
		return true;
	}

	if (1 < level < Y_PLAYER_ADMIN_MAX_LEVEL) {
		return Group_GetPlayer(AdminGroup[level - 1], playerid);
	}

	return false;
}

YCMD:sal(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	new
		targetid,
		level
	;

	SCM(playerid, -1, "WAT");
	// if (sscanf(params, "ud", targetid, level)) return Text_Send();

	return 1;
}