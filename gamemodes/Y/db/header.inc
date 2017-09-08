#if defined _inc_header
	#undef _inc_header
#endif

#include <a_mysql>
#include <a_mysql_yinline>

#define INVALID_DB_ID DBID:0

static stock DBID:__DBID__;

new MySQL:dbhandle;