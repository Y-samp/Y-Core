#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnPlayerLogin(playerid)
{
	inline FetchCars() {
		new rows = cache_num_rows();
		if (!rows) @return 1;

		for (new row = 0; row != rows; ++row) {
			new idx = Iter_Free(PlayerVehicle[playerid]);
			if (idx == INVALID_ITERATOR_SLOT) {
				@return print("PlayerVehicles if full");
			}

			new vid = GetFreeVehicleSlot();
			Player.Vehicle[playerid][index][idx] = vid;
			Iter_Add(PlayerVehicle[playerid], idx);

			cache_get_value_name_int(row, "id", _:Vehicle.Meta[vid][id]);
			cache_get_value_name_int(row, "model", Vehicle.Meta[vid][model]);
			cache_get_value_name_float(row, "X", Vehicle.Status[vid][pos][0]);
			cache_get_value_name_float(row, "Y", Vehicle.Status[vid][pos][1]);
			cache_get_value_name_float(row, "Z", Vehicle.Status[vid][pos][2]);
			cache_get_value_name_float(row, "R", Vehicle.Status[vid][rot]);
			cache_get_value_name_int(row, "color_1", Vehicle.Status[vid][color][0]);
			cache_get_value_name_int(row, "color_2", Vehicle.Status[vid][color][1]);

			CreateVehicle(
				Vehicle.Meta[vid][model],
				Vehicle.Status[vid][pos][0],
				Vehicle.Status[vid][pos][1],
				Vehicle.Status[vid][pos][2],
				Vehicle.Status[vid][rot],
				-1,
				-1,
				-1
			);

			log("Loaded player vehicle in slot %d (dbid %d)", idx, _:Vehicle.Meta[vid][id]);
		}
	}

	new
		query[128]
	;

	mysql_format(dbhandle, query, sizeof query, "SELECT * FROM vehicles WHERE player_id = %d", _:Player.Auth[playerid][id]);	
	mysql_tquery_inline(dbhandle, query, using inline FetchCars);

	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	foreach (new vehicle:PlayerVehicle[playerid]) {
		DestroyVehicle(Player.Vehicle[playerid][index][vehicle]);
	}

	Iter_Clear(PlayerVehicle[playerid]);

	return 1;
}

hook OnPlayerStats(playerid)
{
	new
		vehicles[144],
		i = 1
	;
	foreach (new vehicle:PlayerVehicle[playerid]) {
		format(vehicles, sizeof vehicles, "%s[Vehicle %d]: %d ", vehicles, i, _:Vehicle.Meta[Player.Vehicle[playerid][index][vehicle]][id]);
		i++;
	}

	SCM(playerid, -1, vehicles);

	return 1;	
}

SavePlayerVehicle(playerid, vehicleid)
{
	inline SavedVehicle()
	{
		Vehicle.Meta[vehicleid][id] = DBID:cache_insert_id();
	}

	new query[128];
	mysql_format(
		dbhandle,
		query,
		sizeof query,
		"INSERT INTO vehicles VALUES (null, %d, %d, %.2f, %.2f, %.2f, %.2f, %d, %d)",
		_:Player.Auth[playerid][id],
		Vehicle.Meta[vehicleid][model], Vehicle.Status[vehicleid][pos][0], Vehicle.Status[vehicleid][pos][1], Vehicle.Status[vehicleid][pos][2], 
		Vehicle.Status[vehicleid][rot], Vehicle.Status[vehicleid][color][0], Vehicle.Status[vehicleid][color][1]
	);
	mysql_tquery_inline(dbhandle, query, using inline SavedVehicle);

	return 1;
}