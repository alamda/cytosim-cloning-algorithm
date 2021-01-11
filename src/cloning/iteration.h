#ifndef ITERATION_H
#define ITERATION_H

#include "clone.h"

#include <vector>

typedef struct Iteration_s
{
	float sum_s_a = 0.0;

	int numClonesPredicted = 0 ;

	std::vector < int > genealogy ;

	std::vector < Clone > cloneVector ;

} Iteration ;

#endif // ITERATION_H
