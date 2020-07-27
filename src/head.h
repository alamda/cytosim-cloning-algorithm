#ifndef HEAD_H
#define HEAD_H

#include <vector>

/**	@brief Struct for containing data for a single head of a linker.

	*/

typedef struct Head
{
	int fiberIdentity ;
	float abscissa ;
	std::vector <float> positionVector  ;

	std::vector <float> velocityVector, movementDirVector ;
} Head_t ;

#endif // HEAD_H
