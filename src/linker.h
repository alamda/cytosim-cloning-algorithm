#ifndef LINKER_H
#define LINKER_H

#include "hand.h"

#include <vector>

/**	@brief Struct for containing information of a linker with two hands.

	*/

typedef struct Linker
{
	int classOfObject, linkerIdentity ;
	float force, cosAngle ;

	Hand handOne ;
	Hand handTwo ;

	std::vector <Hand> handObjects ;

	float wDot ;
} Linker ;

#endif // LINKER_H
