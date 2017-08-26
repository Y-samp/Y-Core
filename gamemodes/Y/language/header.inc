#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI\y_languages>

#define MAX_Y_LANGUAGES 5

new
	Language:Languages[MAX_Y_LANGUAGES] = { NO_LANGUAGE, ... }
;