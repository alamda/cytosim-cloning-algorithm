#ifndef LINKER_H
#define LINKER_H

#include "hand.h"

#include <vector>

/**	@brief Struct for containing information of a linker with two hands.

	*/

typedef struct Linker_s
{
	int classOfObject, linkerIdentity, clusterIdentity;
	float force, cosAngle ;

	Hand handOne ;
	Hand handTwo ;

	std::vector <Hand> handObjects ;

	float observable = 0.0;
} Linker ;

#endif // LINKER_H
