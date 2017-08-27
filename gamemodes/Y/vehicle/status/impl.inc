#if defined _inc_impl
	#undef _inc_impl
#endif

hook OnGameModeInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:vpark;
	}

	return 1;
}

UpdateVehicleStatus(vehicleid)
{
	new Float:pos[3], Float:rot;
	GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
	GetVehicleZAngle(vehicleid, rot);

	Vehicle.Status[vehicleid][pos] = pos;
	Vehicle.Status[vehicleid][rot] = rot;

	new query[256];
	mysql_format(
		dbhandle,
		query,
		sizeof query,
		"UPDATE vehicles SET X = %.2f, Y = %.2f, Z = %.2f, R = %.2f, color_1 = %d, color_2 = %d WHERE id = %d",
		Vehicle.Status[vehicleid][pos][0], Vehicle.Status[vehicleid][pos][1], Vehicle.Status[vehicleid][pos][2],
		Vehicle.Status[vehicleid][rot],
		Vehicle.Status[vehicleid][color][0], Vehicle.Status[vehicleid][color][1],
		_:Vehicle.Meta[vehicleid][id]
	);
	mysql_tquery(dbhandle, query, "");
}

YCMD:vpark(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");

	new vid = GetPlayerVehicleID(playerid);
	if (vid == INVALID_VEHICLE_ID) {
		return SCM(playerid, -1, "You are not in a vehicle");
	}

	UpdateVehicleStatus(vid);

	return 1;
}