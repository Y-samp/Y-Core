#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGroupInit()
{
	GROUP_ADD<DeveloperGroup> 
	{
		@YCMD:gotodealership;
	}
}

hook OnScriptInit()
{
	new text[128];

	for (new place = 0; place != _:E_DEALERSHIP_PLACE; ++place) {
		format(text, sizeof text, "[%s dealership]", Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_NAME]);
		CreateDynamic3DTextLabel(text, 0xFFFFFFFF, Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][0], Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][1], Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][2] + 0.5, 20.0, .worldid = 0, .interiorid = 0);
		CreateDynamicPickup(1239, 1, Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][0], Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][1], Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][2], 0, 0);
	}

	DealershipBuyButtonBg = TextDrawCreate(560.0, 180.0, "_");
	TextDrawUseBox(DealershipBuyButtonBg, 1);
	TextDrawTextSize(DealershipBuyButtonBg, 620.0, 30.0);
	TextDrawBoxColor(DealershipBuyButtonBg, 0xFFFFFF33);
	TextDrawLetterSize(DealershipBuyButtonBg, 5.2, 30.0 * 0.135);
	TextDrawSetSelectable(DealershipBuyButtonBg, 1);

	DealershipBuyButton = TextDrawCreate(590.0, 190.0, "BUY");
	TextDrawSetOutline(DealershipBuyButton, 2);
	TextDrawLetterSize(DealershipBuyButton, 0.6, 1.8);
	TextDrawFont(DealershipBuyButton, 2);
	TextDrawAlignment(DealershipBuyButton, 2);
	TextDrawBackgroundColor(DealershipBuyButton, 0x000000FF);

	DealershipPreviousButtonBg = TextDrawCreate(70.0, 370.0, "_");
	TextDrawUseBox(DealershipPreviousButtonBg, 1);
	TextDrawTextSize(DealershipPreviousButtonBg, 170.0, 30.0);
	TextDrawBoxColor(DealershipPreviousButtonBg, 0xFFFFFF33);
	TextDrawLetterSize(DealershipPreviousButtonBg, 5.2, 30.0 * 0.135);
	TextDrawSetSelectable(DealershipPreviousButtonBg, 1);

	DealershipPreviousButton = TextDrawCreate(120.0, 380.0, "<");
	TextDrawSetOutline(DealershipPreviousButton, 2);
	TextDrawLetterSize(DealershipPreviousButton, 0.3, 1.8);
	TextDrawFont(DealershipPreviousButton, 2);
	TextDrawAlignment(DealershipPreviousButton, 2);
	TextDrawBackgroundColor(DealershipPreviousButton, 0x000000FF);

	DealershipNextButtonBg = TextDrawCreate(470.0, 370.0, "_");
	TextDrawUseBox(DealershipNextButtonBg, 1);
	TextDrawTextSize(DealershipNextButtonBg, 570.0, 30.0);
	TextDrawBoxColor(DealershipNextButtonBg, 0xFFFFFF33);
	TextDrawLetterSize(DealershipNextButtonBg, 5.2, 30.0 * 0.135);
	TextDrawSetSelectable(DealershipNextButtonBg, 1);

	DealershipNextButton = TextDrawCreate(520.0, 380.0, ">");
	TextDrawSetOutline(DealershipNextButton, 2);
	TextDrawLetterSize(DealershipNextButton, 0.3, 1.8);
	TextDrawFont(DealershipNextButton, 2);
	TextDrawAlignment(DealershipNextButton, 2);
	TextDrawBackgroundColor(DealershipNextButton, 0x000000FF);

	DealershipRotateButtonBg = TextDrawCreate(250.0, 370.0, "_");
	TextDrawUseBox(DealershipRotateButtonBg, 1);
	TextDrawTextSize(DealershipRotateButtonBg, 390.0, 30.0);
	TextDrawBoxColor(DealershipRotateButtonBg, 0xFFFFFF33);
	TextDrawLetterSize(DealershipRotateButtonBg, 5.2, 30.0 * 0.135);
	TextDrawSetSelectable(DealershipRotateButtonBg, 1);

	DealershipRotateButton = TextDrawCreate(320.0, 380.0, "Rotate");
	TextDrawSetOutline(DealershipRotateButton, 2);
	TextDrawLetterSize(DealershipRotateButton, 0.5, 1.2);
	TextDrawFont(DealershipRotateButton, 2);
	TextDrawAlignment(DealershipRotateButton, 2);
	TextDrawBackgroundColor(DealershipRotateButton, 0x000000FF);

	DealershipVipDiscount = TextDrawCreate(620.0, 160.0, "-10% VIP discount");
	TextDrawSetOutline(DealershipVipDiscount, 2);
	TextDrawLetterSize(DealershipVipDiscount, 0.4, 0.9);
	TextDrawFont(DealershipVipDiscount, 3);
	TextDrawAlignment(DealershipVipDiscount, 3);
	TextDrawBackgroundColor(DealershipVipDiscount, 0x000000FF);
	
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == DealershipRotateButtonBg) {
		new E_DEALERSHIP_CAMERA:mode;
		if (PlayerDealershipCamera[playerid] == E_DEALERSHIP_CAMERA_BACK) {
			mode = E_DEALERSHIP_CAMERA_FRONT;
		} else {
			mode = E_DEALERSHIP_CAMERA:(_:PlayerDealershipCamera[playerid] + 1);
		}

		DealershipSetCamera(playerid, mode);

		return 1;
	}

	if (clickedid == DealershipNextButtonBg) {
		DealershipGetVehicle(playerid, PlayerDealershipVehicle[playerid] + 1);
		return 1;
	}
	if (clickedid == DealershipPreviousButtonBg) {
		DealershipGetVehicle(playerid, PlayerDealershipVehicle[playerid] - 1);
		return 1;
	}
	if (clickedid == DealershipBuyButtonBg) {
		DealershipBuyVehicle(playerid);
		return 1;
	}

	return 1;
}

hook OnPlayerConnect(playerid)
{
	DealershipModelName[playerid] = CreatePlayerTextDraw(playerid, 620.0, 110.0, "ModelName");
	PlayerTextDrawSetOutline(playerid, DealershipModelName[playerid], 2);
	PlayerTextDrawLetterSize(playerid, DealershipModelName[playerid], 0.6, 1.5);
	PlayerTextDrawFont(playerid, DealershipModelName[playerid], 3);
	PlayerTextDrawAlignment(playerid, DealershipModelName[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid, DealershipModelName[playerid], 0x000000FF);

	DealershipPrice[playerid] = CreatePlayerTextDraw(playerid, 620.0, 130.0, "$0");
	PlayerTextDrawSetOutline(playerid, DealershipPrice[playerid], 2);
	PlayerTextDrawLetterSize(playerid, DealershipPrice[playerid], 0.6, 1.8);
	PlayerTextDrawFont(playerid, DealershipPrice[playerid], 3);
	PlayerTextDrawAlignment(playerid, DealershipPrice[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid, DealershipPrice[playerid], 0x000000FF);
	PlayerTextDrawColor(playerid, DealershipPrice[playerid], 0x2DCC0AFF);
}

hook OnPlayerDisconnect(playerid, reason)
{
	PlayerTextDrawDestroy(playerid, DealershipModelName[playerid]);
	PlayerTextDrawDestroy(playerid, DealershipPrice[playerid]);

	if (DealershipVehicle[playerid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(DealershipVehicle[playerid]);
		DealershipVehicle[playerid] = INVALID_VEHICLE_ID;
	}
}

hook OnPlayerEnter(playerid)
{
	for (new place = 0; place != _:E_DEALERSHIP_PLACE; ++place) {
		if (IsPlayerInRangeOfPoint(playerid, 7.0, Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][0], Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][1],  Dealership[E_DEALERSHIP_PLACE:place][E_DEALERSHIP_ENTRANCE][2]) && GetPlayerVirtualWorld(playerid) == 0) {
			DealershipEnter(playerid, E_DEALERSHIP_PLACE:place);

			return 1;
		}
	}

	return 1;
}

hook OnPlayerExit(playerid)
{
	if (PlayerDealership[playerid] != INVALID_DEALERSHIP) {
		DealershipExit(playerid);
	}

	return 1;
}

#define CurrentDealership Dealership[PlayerDealership[playerid]]
#define CurrentDealershipVehicle DealershipVehicles[PlayerDealership[playerid]][PlayerDealershipVehicle[playerid]]
DealershipEnter(playerid, E_DEALERSHIP_PLACE:index)
{
	PlayerDealership[playerid] = index;
	SCM(playerid, -1, "Entered %s dealership", CurrentDealership[E_DEALERSHIP_NAME]);
	TogglePlayerSpectating(playerid, 1);
	SetPlayerVirtualWorld(playerid, MAX_PLAYERS + playerid);
	SetPlayerPos(playerid, 1187.8796, -1322.4230, 13.5665);

	defer DealershipFixSpectate(playerid);
	SelectTextDraw(playerid, 0x000000CC);

	DealershipGetVehicle(playerid, 0);

	TextDrawShowForPlayer(playerid, DealershipBuyButtonBg);
	TextDrawShowForPlayer(playerid, DealershipBuyButton);
	TextDrawShowForPlayer(playerid, DealershipNextButtonBg);
	TextDrawShowForPlayer(playerid, DealershipNextButton);
	TextDrawShowForPlayer(playerid, DealershipPreviousButtonBg);
	TextDrawShowForPlayer(playerid, DealershipPreviousButton);
	TextDrawShowForPlayer(playerid, DealershipRotateButtonBg);
	TextDrawShowForPlayer(playerid, DealershipRotateButton);

	#if defined Y_PLAYER_REQUIRE_ACCOUNT
	if (Player.Status[playerid][vip]) {
		TextDrawShowForPlayer(playerid, DealershipVipDiscount);
	}
	#endif

	PlayerTextDrawShow(playerid, DealershipModelName[playerid]);
	PlayerTextDrawShow(playerid, DealershipPrice[playerid]);
}

DealershipExit(playerid)
{
	SetCameraBehindPlayer(playerid);
	TogglePlayerSpectating(playerid, 0);

	SetPlayerVirtualWorld(playerid, 0);
	CancelSelectTextDraw(playerid);

	SetPlayerPos(playerid, CurrentDealership[E_DEALERSHIP_ENTRANCE][0], CurrentDealership[E_DEALERSHIP_ENTRANCE][1], CurrentDealership[E_DEALERSHIP_ENTRANCE][2]);

	if (DealershipVehicle[playerid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(DealershipVehicle[playerid]);
		DealershipVehicle[playerid] = INVALID_VEHICLE_ID;
	}

	TextDrawHideForPlayer(playerid, DealershipBuyButtonBg);
	TextDrawHideForPlayer(playerid, DealershipBuyButton);
	TextDrawHideForPlayer(playerid, DealershipNextButtonBg);
	TextDrawHideForPlayer(playerid, DealershipNextButton);
	TextDrawHideForPlayer(playerid, DealershipPreviousButtonBg);
	TextDrawHideForPlayer(playerid, DealershipPreviousButton);
	TextDrawHideForPlayer(playerid, DealershipRotateButtonBg);
	TextDrawHideForPlayer(playerid, DealershipRotateButton);

	#if defined Y_PLAYER_REQUIRE_ACCOUNT
	if (Player.Status[playerid][vip]) {
		TextDrawHideForPlayer(playerid, DealershipVipDiscount);
	}
	#endif
 
	PlayerTextDrawHide(playerid, DealershipModelName[playerid]);
	PlayerTextDrawHide(playerid, DealershipPrice[playerid]);

	PlayerDealership[playerid] = INVALID_DEALERSHIP;
}

DealershipGetVehicle(playerid, index)
{
	if (DealershipVehicle[playerid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(DealershipVehicle[playerid]);
	}

	PlayerDealershipVehicle[playerid] = index;

	if (index == CurrentDealership[E_DEALERSHIP_TOTAL_VEHICLES]) {
		PlayerDealershipVehicle[playerid] = 0;
	} else if (index < 0) {
		PlayerDealershipVehicle[playerid] = CurrentDealership[E_DEALERSHIP_TOTAL_VEHICLES] - 1;
	}

	PlayerTextDrawSetString(playerid, DealershipModelName[playerid], Model_Name(CurrentDealershipVehicle[E_DEALERSHIP_CAR_MODEL]));

	new 
		price = GetModelPrice(CurrentDealershipVehicle[E_DEALERSHIP_CAR_MODEL]),
		priceText[64]
	;

	format(priceText, sizeof priceText, "$%d", price);

	PlayerTextDrawColor(playerid, DealershipPrice[playerid], GetPlayerMoney(playerid) < DealershipGetPrice(playerid) ? 0xD60606FF : 0x52B700FF);

	PlayerTextDrawSetString(playerid, DealershipPrice[playerid], priceText);
	PlayerTextDrawHide(playerid, DealershipModelName[playerid]);
	PlayerTextDrawHide(playerid, DealershipPrice[playerid]);
	PlayerTextDrawShow(playerid, DealershipModelName[playerid]);
	PlayerTextDrawShow(playerid, DealershipPrice[playerid]);

	DealershipVehicle[playerid] = CreateVehicle(CurrentDealershipVehicle[E_DEALERSHIP_CAR_MODEL], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][0], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][1], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][2], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][3], 0, 0, -1);
	SetVehicleVirtualWorld(DealershipVehicle[playerid], MAX_PLAYERS + playerid);
}

DealershipGetPrice(playerid)
{
	new price = GetModelPrice(CurrentDealershipVehicle[E_DEALERSHIP_CAR_MODEL]);

	#if defined Y_PLAYER_REQUIRE_ACCOUNT
	if (Player.Status[playerid][vip]) {
		price -= floatround(price * 0.1);
	}
	#endif

	return price;
}

DealershipSetCamera(playerid, E_DEALERSHIP_CAMERA:mode = E_DEALERSHIP_CAMERA_FRONT)
{
	PlayerDealershipCamera[playerid] = mode;

	switch(mode)
	{
		case E_DEALERSHIP_CAMERA_FRONT: {
			SetPlayerCameraPos(playerid, CurrentDealership[E_DEALERSHIP_CAMERA_POS_FRONT][0], CurrentDealership[E_DEALERSHIP_CAMERA_POS_FRONT][1], CurrentDealership[E_DEALERSHIP_CAMERA_POS_FRONT][2]);
		}
		case E_DEALERSHIP_CAMERA_SIDE: {
			SetPlayerCameraPos(playerid, CurrentDealership[E_DEALERSHIP_CAMERA_POS_SIDE][0], CurrentDealership[E_DEALERSHIP_CAMERA_POS_SIDE][1], CurrentDealership[E_DEALERSHIP_CAMERA_POS_SIDE][2]);
		}
		case E_DEALERSHIP_CAMERA_BACK: {
			SetPlayerCameraPos(playerid, CurrentDealership[E_DEALERSHIP_CAMERA_POS_BACK][0], CurrentDealership[E_DEALERSHIP_CAMERA_POS_BACK][1], CurrentDealership[E_DEALERSHIP_CAMERA_POS_BACK][2]);
		}
	}

	SetPlayerCameraLookAt(playerid, CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][0], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][1], CurrentDealership[E_DEALERSHIP_VEHICLE_POSITION][2]);
}

DealershipBuyVehicle(playerid)
{
	new price = DealershipGetPrice(playerid);

	if (GetPlayerMoney(playerid) < price) {
		return SCM(playerid, -1, "You can't afford that vehicle");
	}

	#if defined Y_PLAYER_VEHICLE_ENABLED
		new slot = Iter_Free(PlayerVehicle[playerid]);
		if(slot == INVALID_ITERATOR_SLOT) {
			return SCM(playerid, -1, "You already own maximum number of vehicles!");
		}
	#endif

	GivePlayerMoney(playerid, -price);

	new vehicle = GetFreeVehicleSlot();

	log("Vehicle bought for %d with index %d", playerid, vehicle);

	#if defined Y_PLAYER_VEHICLE_ENABLED
		Player.Vehicle[playerid][index][slot] = vehicle;
	#endif

	Vehicle.Status[vehicle][pos][0] = CurrentDealership[E_DEALERSHIP_VEHICLE_SPAWN][0];
	Vehicle.Status[vehicle][pos][1] = CurrentDealership[E_DEALERSHIP_VEHICLE_SPAWN][1];
	Vehicle.Status[vehicle][pos][2] = CurrentDealership[E_DEALERSHIP_VEHICLE_SPAWN][2];
	Vehicle.Status[vehicle][rot] = CurrentDealership[E_DEALERSHIP_VEHICLE_SPAWN][3];
	Vehicle.Meta[vehicle][model] = _:CurrentDealershipVehicle[E_DEALERSHIP_CAR_MODEL];

	SCM(playerid, -1, ":_______VEHICLE PURCHASED_______:");
	SCM(playerid, -1, "REMEMBER: Leaving your vehicle in the delivery point can get your vehicle deleted by the administration without refund!");

	CreateVehicle(
		Vehicle.Meta[vehicle][model],
		Vehicle.Status[vehicle][pos][0], Vehicle.Status[vehicle][pos][1], Vehicle.Status[vehicle][pos][2],
		Vehicle.Status[vehicle][rot],
		1, 1,	-1
	);

	#if defined Y_PLAYER_VEHICLE_ENABLED
		SavePlayerVehicle(playerid, vehicle);
	#endif

	DealershipExit(playerid);
	PutPlayerInVehicle(playerid, vehicle, 0);

	return 1;
}

timer DealershipFixSpectate[200](playerid)
{
	DealershipSetCamera(playerid);
}

#undef CurrentDealership
#undef CurrentDealershipVehicle

YCMD:gotodealership(playerid, params[], help)
{
	if(help) return SCM(playerid, -1, "Not supported");
  
	new list[128];
	strcpy(list, "1\tSports\n2\tLowriders\n3\tSaloons C&S\n4\tSaloons Pick and Go\n5\tOff Road\n6\tAircrafts\n7\tBoats\n8\tTrucks\n9\tMotorbikes");

	#if defined Y_PLAYER_REQUIRE_ACCOUNT
	if (Player.Status[playerid][vip]) {
		strcat(list, "\n10\tVIP");
	}
	#endif

	inline Response(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, response, listitem, inputtext

		if(!response) continue;
		
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][0], Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][1], Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][2]);
		}
		else
		{
			SetPlayerPos(playerid, Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][0], Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][1], Dealership[E_DEALERSHIP_PLACE:listitem][E_DEALERSHIP_ENTRANCE][2]);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}

	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST,"Dealerships:",list,"Tele","Cancel");

	return 1;
}