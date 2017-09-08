#if defined _inc_header
	#undef _inc_header
#endif

#define Player. OO_TYPE(PLAYER,Player)

// static stock @vb:foo;

#define ALS_DO_PlayerEnter<%0> %0<PlayerEnter,i>(end:playerid)

new
	Group:DeveloperGroup
;

#define IsDeveloper(%0) Group_GetPlayer(DeveloperGroup, %0)

#define ALS_DO_PlayerStats<%0> %0<PlayerStats,i>(end:playerid)