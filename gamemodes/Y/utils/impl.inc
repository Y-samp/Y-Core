#if defined _inc_impl
	#undef _inc_impl
#endif

timer TimedKick[100](playerid)
{
	return Kick(playerid);
}

stock randomString(dest[], len)
{
	while(len--) {
		dest[len] = random(2) ? (random(26) + (random(2) ? 'a' : 'A')) : (random(10) + '0');
	}
}