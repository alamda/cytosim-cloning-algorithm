#ifndef HEAD_H
#define HEAD_H

#include <vector>

typedef struct Head
{
	int fiberIdentity ;
	float abscissa ;
	std::vector <float> positionVector  ;

	std::vector <float> velocityVector, movementDirVector ;
} Head_t ;

#endif // HEAD_H
