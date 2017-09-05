#if defined _inc_header
	#undef _inc_header
#endif

#if !defined Y_PLAYER_ENABLED
	#error Y vehicle requires Y players to be enabled
#endif

#include <YSI\y_commands>
#include <YSI\y_text>

#define Vehicle. OO_TYPE(VEHICLE,Vehicle)

// Vehicle information that does not change
enum E_VEHICLE_META {
	DBID:E_VEHICLE_Meta_id,
	E_VEHICLE_Meta_model
}

// Working using default Vehicle iterator
new VehicleMeta[MAX_VEHICLES][E_VEHICLE_META];