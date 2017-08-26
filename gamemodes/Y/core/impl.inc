#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

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
			printf("Other mysql error %d %s (callback %s)", errorid, error, callback);
		}
	}
	return 1;
}