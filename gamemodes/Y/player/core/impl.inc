#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	DeveloperGroup = Group_Create("Developer");

	return 1;
}

hook OnGroupInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:enter;
	}

	return 1;
}

YCMD:enter(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	call OnPlayerEnter(playerid);	

	return 1;
}