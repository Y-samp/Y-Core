Test:generateSalt()
{
	new dest[20 + 1];
	GenerateSalt(dest);
	ASSERT(strlen(dest) == 20);
}