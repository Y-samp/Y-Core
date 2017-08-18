hook OnGameModeInit()
{
	mysql_log(ALL);

	new MySQLOpt:options = mysql_init_options();
	mysql_set_option(options, POOL_SIZE, MYSQL_POOL_SIZE);

	dbhandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, options);

	if (dbhandle == MYSQL_INVALID_HANDLE || mysql_errno(dbhandle) != 0) {
		print("MySQL connection failed. Server is shutting down.");
		SendRconCommand("exit");
	} else {
		print("MySQL connection established");
	}
	
	return 1;
}

hook OnGameModeExit()
{
	mysql_close(dbhandle);

	return 1;
}