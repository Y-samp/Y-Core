Test:randomString()
{
	new dst[32];
	randomString(dst, 32);
	ASSERT(strlen(dst) == 32);
}