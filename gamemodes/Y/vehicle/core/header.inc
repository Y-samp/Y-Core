#if defined _inc_header
	#undef _inc_header
#endif

#if !defined Y_PLAYER_ENABLED
	#error Y vehicle requires Y players to be enabled
#endif

#define Vehicle.%0[%1][%2] Vehicle%0[%1][E_VEHICLE_%0_%2]

// Vehicle information that does not change
enum E_VEHICLE_META {
	DBID:E_VEHICLE_Meta_id,
	E_VEHICLE_Meta_model
}

// Working using default Vehicle iterator
new VehicleMeta[MAX_VEHICLES][E_VEHICLE_META];