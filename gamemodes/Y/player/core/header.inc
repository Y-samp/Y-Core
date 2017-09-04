#if defined _inc_header
	#undef _inc_header
#endif

#define Player.%0[%1] (_:@vb:@va:Player@%0[%1]
#define @va:Player@%0[%1][@%2] Player%0[%1])[E_PLAYER_%0_%2]
#define @vb:@va:Player@%0[%1][%2][@%3] Player%0[%1])[%2][E_PLAYER_%0_%3]

// static stock @vb:foo;

#define ALS_DO_PlayerEnter<%0> %0<PlayerEnter,i>(end:playerid)

new
	Group:DeveloperGroup
;

#define IsDeveloper(%0) (Group_GetPlayer(DeveloperGroup, %0))

#define ALS_DO_PlayerStats<%0> %0<PlayerStats,i>(end:playerid)