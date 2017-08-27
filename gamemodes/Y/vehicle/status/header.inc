#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_commands>

enum E_VEHICLE_STATUS {
	Float:E_VEHICLE_Status_pos[3],
	Float:E_VEHICLE_Status_rot,
	E_VEHICLE_Status_color[2]
}

new VehicleStatus[MAX_VEHICLES][E_VEHICLE_STATUS];