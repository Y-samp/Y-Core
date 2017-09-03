#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_@@@@_HEADER
	#include "core\header"
	#include "db\header"
	#include "log\header"
	#include "debug\header"
	#include "utils\header"
	#include "language\header"

	#if defined Y_PLAYER_ENABLED
		#include "player\header"
	#endif

	#if defined Y_VEHICLE_ENABLED
		#include "vehicle\header"
	#endif

	#if defined Y_OBJECT_ENABLED
		#include "object\header"
	#endif

	#if defined Y_MODE_RP
		#include "RP\RP"
	#endif

	#define Y_@@@@_HEADER
#elseif !defined Y_@@@@_END
	#include "core\impl"
	#include "db\impl"
	#include "debug\impl"
	#include "utils\impl"
	#include "language\impl"

	#if defined Y_PLAYER_ENABLED
		#include "player\impl"
	#endif

	#if defined Y_VEHICLE_ENABLED
		#include "vehicle\impl"
	#endif

	#if defined Y_OBJECT_ENABLED
		#include "object\impl"
	#endif

	#if defined Y_MODE_RP
		#include "RP\RP"
	#endif
	#define Y_@@@@_END
#else
	#error Y core already set up
#endif