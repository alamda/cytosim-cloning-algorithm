#ifndef LINKER_H
#define LINKER_H

#include <cstdio>
#include <vector>
#include "head.h"

typedef struct Linker
{
	int classOfObject, linkerIdentity ;
	float force, cos_angle ;

	Head headOne ;
	Head headTwo ;

	std::vector <Head> headObjects ;
} Linker_t ;

#endif // LINKER_H
