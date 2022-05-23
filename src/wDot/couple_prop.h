#ifndef COUPLE_PROP_H
#define COUPLE_PROP_H

#include "hand_prop.h"

/**	@brief	Struct containing parameters for a couple
	*/

typedef struct Couple_Prop_s
{
	std::string name ;
	std::string propertyNumber ;

	Hand_Prop handPropOne ;
	Hand_Prop handPropTwo ;

} Couple_Prop ;

#endif // COUPLE_PROP_H
