#if defined _inc_impl
	#undef _inc_impl
#endif

GetVehicleIDFromDBID(dbid)
{
	foreach (new vehicle:Vehicle) {
		if (VehicleMeta[vehicle][id] == dbid) {
			return dbid;
		}
	}

	return INVALID_VEHICLE_ID;
}

GetFreeVehicleSlot()
{
	Iter_Add(Vehicle, 0);
	new slot = Iter_Free(Vehicle);
	Iter_Remove(Vehicle, 0);

	return slot;
}

GetModelPrice(model)
{
	if(model == 400) return 40000;
	else if(model == 401) return 30000;
	else if(model == 402) return 100000;
	else if(model == 403) return 90000;
	else if(model == 404) return 25000;
	else if(model == 405) return 40000;
	else if(model == 406) return 200000;
	else if(model == 408) return 80000;
	else if(model == 409) return 90000;
	else if(model == 410) return 25000;
	else if(model == 411) return 150000;
	else if(model == 412) return 60000;
	else if(model == 413) return 55000;
	else if(model == 414) return 75000;
	else if(model == 415) return 100000;
	else if(model == 417) return 250000;
	else if(model == 418) return 20000;
	else if(model == 419) return 30000;
	else if(model == 421) return 75000;
	else if(model == 422) return 60000;
	else if(model == 423) return 100000;
	else if(model == 424) return 85000;
	else if(model == 426) return 80000;
	else if(model == 428) return 40000;
	else if(model == 429) return 125000;
	else if(model == 434) return 150000;
	else if(model == 436) return 45000;
	else if(model == 439) return 55000;
	else if(model == 443) return 100000;
	else if(model == 444) return 175000;
	else if(model == 445) return 75000;
	else if(model == 446) return 175000;
	else if(model == 451) return 150000;
	else if(model == 452) return 175000;
	else if(model == 453) return 125000;
	else if(model == 454) return 130000;
	else if(model == 455) return 80000;
	else if(model == 456) return 70000;
	else if(model == 457) return 85000;
	else if(model == 458) return 50000;
	else if(model == 459) return 60000;
	else if(model == 460) return 215000;
	else if(model == 461) return 40000;
	else if(model == 462) return 20000;
	else if(model == 463) return 35000;
	else if(model == 466) return 70000;
	else if(model == 467) return 70000;
	else if(model == 468) return 35000;
	else if(model == 469) return 175000;
	else if(model == 471) return 15000;
	else if(model == 473) return 125000;
	else if(model == 474) return 65000;
	else if(model == 475) return 65000;
	else if(model == 477) return 100000;
	else if(model == 478) return 40000;
	else if(model == 479) return 75000;
	else if(model == 480) return 150000;
	else if(model == 481) return 5000;
	else if(model == 482) return 65000;
	else if(model == 483) return 70000;
	else if(model == 484) return 125000;
	else if(model == 485) return 30000;
	else if(model == 486) return 150000;
	else if(model == 487) return 200000;
	else if(model == 489) return 75000;
	else if(model == 491) return 60000;
	else if(model == 492) return 70000;
	else if(model == 493) return 200000;
	else if(model == 494) return 100000;
	else if(model == 495) return 90000;
	else if(model == 496) return 60000;
	else if(model == 498) return 80000;
	else if(model == 499) return 80000;
	else if(model == 500) return 70000;
	else if(model == 502) return 100000;
	else if(model == 503) return 100000;
	else if(model == 504) return 100000;
	else if(model == 505) return 75000;
	else if(model == 506) return 115000;
	else if(model == 507) return 75000;
	else if(model == 508) return 50000;
	else if(model == 509) return 2500;
	else if(model == 510) return 10000;
	else if(model == 511) return 215000;
	else if(model == 512) return 200000;
	else if(model == 513) return 220000;
	else if(model == 514) return 90000;
	else if(model == 515) return 90000;
	else if(model == 516) return 67500;
	else if(model == 517) return 70000;
	else if(model == 518) return 65000;
	else if(model == 519) return 300000;
	else if(model == 521) return 35000;
	else if(model == 522) return 75000;
	else if(model == 524) return 80000;
	else if(model == 526) return 65000;
	else if(model == 527) return 65000;
	else if(model == 529) return 70000;
	else if(model == 530) return 90000;
	else if(model == 531) return 40000;
	else if(model == 532) return 200000;
	else if(model == 533) return 70000;
	else if(model == 534) return 76000;
	else if(model == 535) return 80000;
	else if(model == 536) return 75000;
	else if(model == 539) return 150000;
	else if(model == 540) return 70000;
	else if(model == 541) return 150000;
	else if(model == 542) return 80000;
	else if(model == 543) return 50000;
	else if(model == 545) return 125000;
	else if(model == 546) return 70000;
	else if(model == 547) return 70000;
	else if(model == 549) return 60000;
	else if(model == 550) return 90000;
	else if(model == 551) return 80000;
	else if(model == 552) return 30000;
	else if(model == 553) return 250000;
	else if(model == 554) return 50000;
	else if(model == 555) return 50000;
	else if(model == 556) return 200000;
	else if(model == 557) return 200000;
	else if(model == 558) return 70000;
	else if(model == 559) return 70000;
	else if(model == 560) return 115000;
	else if(model == 561) return 50000;
	else if(model == 562) return 95000;
	else if(model == 563) return 200000;
	else if(model == 565) return 90000;
	else if(model == 566) return 70000;
	else if(model == 567) return 75000;
	else if(model == 568) return 50000;
	else if(model == 571) return 85000;
	else if(model == 572) return 15000;
	else if(model == 573) return 90000;
	else if(model == 575) return 80000;
	else if(model == 576) return 65000;
	else if(model == 578) return 90000;
	else if(model == 579) return 90000;
	else if(model == 580) return 75000;
	else if(model == 581) return 30000;
	else if(model == 583) return 25000;
	else if(model == 585) return 35000;
	else if(model == 586) return 20000;
	else if(model == 587) return 90000;
	else if(model == 588) return 90000;
	else if(model == 589) return 90000;
	else if(model == 592) return 350000;
	else if(model == 593) return 225000;
	else if(model == 600) return 50000;
	else if(model == 602) return 75000;
	else if(model == 603) return 100000;
	else if(model == 609) return 85000;
	else return 0;
}