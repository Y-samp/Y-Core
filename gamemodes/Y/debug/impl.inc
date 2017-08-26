#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	GROUP_ADD<DeveloperGroup>
	{
		@YCMD:setmoney;
	}

	return 1;
}

YCMD:setmoney(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");
	new money;

	if (sscanf(params, "d", money)) return SCM(playerid, -1, "/setmoney [money]");

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, money);

	return 1;
}