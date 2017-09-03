#if defined _inc_header
	#undef _inc_header
#endif

#if defined Y_DEBUG
	#define log printf
	#define err printf
#else
	log(...) {}
	err(...) {}
#endif