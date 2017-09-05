#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_groups>
#include <YSI\y_colours>
#include <YSI\y_commands>
#include <YSI\y_master>

#define OO_TYPE(%6,%7)%0[%1] (_:@vb:@va:%6:%7@%0[%1]
#define @va:%6:%7@%0[%1][@%2] %7%0[%1])[E_%6_%0_%2]
#define @vb:@va:%6:%7@%0[%1][%2][@%3] %7%0[%1])[%2][E_%6_%0_%3]

#define SCM va_SendClientMessage

#define ALS_DO_GroupInit<%0> %0<GroupInit,>(none:)

new
	LoadedSystems = 0,
	TotalSystems = 0
;