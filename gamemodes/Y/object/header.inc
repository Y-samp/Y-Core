#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_timers>

#define MAX_OBJECT_NAME 32

new
	TotalObjects = 0,
	LoadedObjects = 0
;

enum E_OBJECT {
	DBID:E_OBJECT_id,
	E_OBJECT_model,
	Float:E_OBJECT_pos[3],
	Float:E_OBJECT_rot[3],
	E_OBJECT_int,
	E_OBJECT_world,
	E_OBJECT_object
}

new _Object[Y_OBJECT_TOTAL][E_OBJECT];
new Iterator:Object<Y_OBJECT_TOTAL>;

#define Object[%1][@%2] _Object[%1][E_OBJECT_%2]

#define ALS_DO_LoadObjects<%0> %0<LoadObjects,>(none:)

#define OBJECT_TABLE "objects"