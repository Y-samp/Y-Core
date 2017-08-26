#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_commands>
#include <YSI\y_groups>
#include <YSI\y_vehicledata>

#define INVALID_DEALERSHIP (E_DEALERSHIP_PLACE:-1)
#define INVALID_DEALERSHIP_CAR (-1)
#define MAX_DEALERSHIP_CARS (31)

enum E_DEALERSHIP
{
	E_DEALERSHIP_NAME[32],
	Float:E_DEALERSHIP_ENTRANCE[3],
	Float:E_DEALERSHIP_VEHICLE_SPAWN[4],
	Float:E_DEALERSHIP_VEHICLE_POSITION[4],
	Float:E_DEALERSHIP_CAMERA_POS_FRONT[3],
	Float:E_DEALERSHIP_CAMERA_POS_SIDE[3],
	Float:E_DEALERSHIP_CAMERA_POS_BACK[3],
	E_DEALERSHIP_TOTAL_VEHICLES
}

enum E_DEALERSHIP_CAR
{
	E_DEALERSHIP_CAR_MODEL
}

enum E_DEALERSHIP_CAMERA
{
	E_DEALERSHIP_CAMERA_FRONT,
	E_DEALERSHIP_CAMERA_SIDE,
	E_DEALERSHIP_CAMERA_BACK
}

enum E_DEALERSHIP_PLACE
{
	E_DEALERSHIP_PLACE_SPORTS,
	E_DEALERSHIP_PLACE_LOWRIDERS,
	E_DEALERSHIP_PLACE_SALOONS_1,
	E_DEALERSHIP_PLACE_SALOONS_2,
	E_DEALERSHIP_PLACE_OFFROAD,
	E_DEALERSHIP_PLACE_AIRCRAFTS,
	E_DEALERSHIP_PLACE_BOATS,
	E_DEALERSHIP_PLACE_TRUCKS,
	E_DEALERSHIP_PLACE_MOTORBIKES,
	E_DEALERSHIP_PLACE_VIP
}

new 
	Text:DealershipBuyButton,
	Text:DealershipBuyButtonBg,
	Text:DealershipNextButton,
	Text:DealershipNextButtonBg,
	Text:DealershipPreviousButton,
	Text:DealershipPreviousButtonBg,
	Text:DealershipRotateButton,
	Text:DealershipRotateButtonBg,
	Text:DealershipVipDiscount,
	PlayerText:DealershipModelName[MAX_PLAYERS],
	PlayerText:DealershipPrice[MAX_PLAYERS]
;

new
	E_DEALERSHIP_PLACE:PlayerDealership[MAX_PLAYERS] = { INVALID_DEALERSHIP, ... },
	PlayerDealershipVehicle[MAX_PLAYERS] = { INVALID_DEALERSHIP_CAR, ... },
	E_DEALERSHIP_CAMERA:PlayerDealershipCamera[MAX_PLAYERS] = { E_DEALERSHIP_CAMERA_FRONT, ... },
	Dealership[E_DEALERSHIP_PLACE][E_DEALERSHIP] = {
		{
			"Sports",
			{ 544.2350,-1290.2289,17.2422 },
			{ 555.9735,-1265.5007,17.2422,1.4152 },
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			20
		},
		{
			"Lowriders",
			{ 300.2710, -1519.6945, 24.6007 }, // lowrider start
			{ 307.6008, -1507.6388, 24.5938, 323.4597 },
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			9
		},
		{
			"Saloons C&S",
			{ 2131.6594, -1149.7532, 24.2308 }, // saloons enter
			{ 2125.4016, -1129.4315, 25.4972, 0.9348 },
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			12
		},
		{
			"Saloons Pick and Go",
			{ 2139.4172, -1168.7051, 23.9922 }, // saloons enter
			{ 2160.9226, -1168.2184, 23.8200, 88.9221 },
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			23
		},
		{
			"Offroad",
			{ 2520.2568, -1519.0847, 23.9407 }, // offroad enter
			{ 2504.7729, -1520.4708, 23.8900, 4.9220 },
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			21
		},
		{
			"Aircrafts",
			{ 1749.5895, -2548.6216, 13.5469 },  // aircraft enter
			{ 1766.0347, -2547.2693, 13.5469, 273.1562 }, // aircraft spawn
			{ 1805.4435, -2546.9824, 13.8294, 90.4264 },
			{ 1819.3917, -2547.7112, 13.5469 },
			{ 1803.8776, -2562.4329, 13.5469 },
			{ 1789.4686, -2548.0947, 13.5469 },
			13
		},
		{
			"Boats",
			{ 2499.2412, -2261.8318, 3.0000 }, // boats enter
			{ 2499.6501, -2268.9026, 2.1963, 268.9758 },
			{ 2519.6501, -2268.9026, 2.1963, 268.9758 },
			{ 2485.3464, -2268.2927, 3.4805 },
			{ 2497.6040, -2275.4026, 3.6807 },
			{ 2513.3428, -2269.8833, 3.3132 },
			5
		},
		{
			"Trucks",
			{ 1099.9951, -1202.0293, 17.8047 }, // trucks enter
			{ 1092.7864, -1207.6033, 17.8047, 90.5855 }, // trucks spawn
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			14
		},
		{
			"Motorbikes",
			{ 2794.6833, -1619.2235, 10.9219 }, // motorbikes enter
			{ 2793.7437, -1608.5442, 10.9219, 346.3281 }, // motorbikes spawn
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			11
		},
		{
			"VIP",
			{ 1024.8635, -982.9116, 42.6615 }, // vip enter
			{ 1036.0011, -975.7188, 42.5649, 318.8642 }, // vip spawn
			{ -1950.4407, 264.6349, 41.0471, 181.4166 },
			{ -1950.6555, 256.2453, 41.0534 },
			{ -1958.0184, 265.1506, 41.0471 },
			{ -1950.2700, 274.1118, 41.0471 },
			9
		}
	},
	DealershipVehicles[E_DEALERSHIP_PLACE][MAX_DEALERSHIP_CARS][E_DEALERSHIP_CAR] = {
		{ { 587 }, { 589 }, { 429 }, { 602 }, { 402 }, { 559 }, { 603 }, { 558 }, { 458 }, { 475 }, { 565 }, { 415 }, { 541 }, { 477 }, { 496 }, { 545 }, { 480 }, { 533 }, { 439 }, { 555 }, { -1 }, { -1 }, ... },
		{ { 536 }, { 561 }, { 575 }, { 567 }, { 534 }, { 576 }, { 412 }, { 535 }, { 566 }, { -1 }, { -1 }, ... },
		{ { 418 }, { 527 }, { 507 }, { 542 }, { 562 }, { 445 }, { 419 }, { 585 }, { 518 }, { 504 }, { 401 }, { 479 }, { -1 }, { -1 }, ... },
		{ { 404 }, { 526 }, { 540 }, { 491 }, { 529 }, { 549 }, { 466 }, { 551 }, { 516 }, { 410 }, { 426 }, { 436 }, { 580 }, { 405 }, { 547 }, { 560 }, { 517 }, { 546 }, { 474 }, { 550 }, { 492 }, { 567 }, { 421 }, { -1 }, { -1 }, ... },
		{ { 422 }, { 543 }, { 413 }, { 600 }, { 459 }, { 552 }, { 554 }, { 568 }, { 424 }, { 400 }, { 579 }, { 505 }, { 489 }, { 500 }, { 588 }, { 573 }, { 508 }, { 495 }, { 483 }, { 434 }, { 423 }, { -1 }, { -1 }, ... },
		{ { 519 }, { 511 }, { 487 }, { 469 }, { 563 }, { 447 }, { 417 }, { 513 }, { 512 }, { 553 }, { 577 }, { 592 }, { 593 }, { -1 }, { -1 }, ... },
		{ { 484 }, { 452 }, { 454 }, { 473 }, { 446 }, { -1 }, { -1 }, ... },
		{ { 609 }, { 498 }, { 578 }, { 414 }, { 524 }, { 455 }, { 403 }, { 514 }, { 515 }, { 428 }, { 456 }, { 443 }, { 485 }, { 583 }, { -1 }, { -1 }, ... },
		{ { 586 }, { 468 }, { 463 }, { 471 }, { 457 }, { 509 }, { 481 }, { 510 }, { 521 }, { 461 }, { 581 }, { -1 }, { -1 }, ... },
		{ { 494 }, { 502 }, { 503 }, { 539 }, { 571 }, { 556 }, { 557 }, { 444 }, { 522 }, { -1 }, { -1 }, ... }
	},        
	DealershipVehicle[MAX_PLAYERS] = { INVALID_VEHICLE_ID, ... }
;