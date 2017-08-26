#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	LoggedGroup = Group_Create("Logged in");

	return 1;
}