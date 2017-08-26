#if defined _inc_header
	#undef _inc_header
#endif

#define Player.%0[%1][%2] Player%0[%1][E_PLAYER_%0_%2]

#define ALS_DO_PlayerEnter<%0> %0<PlayerEnter,i>(end:playerid)

new
	Group:DeveloperGroup
;