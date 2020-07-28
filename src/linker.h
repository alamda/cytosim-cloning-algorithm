#ifndef LINKER_H
#define LINKER_H

#include "head.h"

#include <vector>

/**	@brief Struct for containing information of a linker with two heads.

	*/

typedef struct Linker
{
	int classOfObject, linkerIdentity ;
	float force, cosAngle ;

	Head headOne ;
	Head headTwo ;

	std::vector <Head> headObjects ;
} Linker_t ;

#endif // LINKER_H
