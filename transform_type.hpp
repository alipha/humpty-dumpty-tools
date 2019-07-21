#ifndef TRANSFORM_TYPE_HPP
#define TRANSFORM_TYPE_HPP


enum transform_type {
	NONE =         000,
	ALL_LOWER =    001,
	ALL_UPPER =    002,
	CAPITALIZE =   004,
	MIXED =        007,	// the number of transformations done is word length dependant :-/
	LEET_NUMBERS = 010, // all or nothing?
	LEET_SYMBOLS = 020	// all or nothing?
};


#endif
