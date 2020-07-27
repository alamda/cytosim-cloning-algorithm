#ifndef LINKER_H
#define LINKER_H

#include <vector>
#include "head.h"

/**	@brief Struct for containing information of a linker with two heads.

	*/

typedef struct Linker
{
	int classOfObject, linkerIdentity ;
	float force, cos_angle ;

	Head headOne ;
	Head headTwo ;

	std::vector <Head> headObjects ;
} Linker_t ;

#endif // LINKER_H
