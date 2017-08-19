#include <a_mysql>
#include <a_samp>
#include "config"
#include "Y\db"

public OnGameModeInit()
{
	print("Loading players table");
	if(!mysql_tquery_file(dbhandle, "Y/migrations/players.sql", "OnPlayersLoaded")) {
		print("Loading players failed");
	}

	return 1;
}

forward OnPlayersLoaded();
public OnPlayersLoaded()
{
	print("Players table loaded");
	return 1;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case CR_SERVER_GONE_ERROR: {
			print("Lost connection to server");
		}
		case ER_SYNTAX_ERROR: {
			printf("Something is wrong in your syntax, query: %s",query);
		}
		default: {
			printf("Other error %d %s", errorid, error);
		}
	}
	return 1;
}