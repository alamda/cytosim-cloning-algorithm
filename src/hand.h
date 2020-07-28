#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Eigen/Dense"

/**	@brief Struct for containing data for a single hand of a linker.

	*/

typedef struct Hand
{
	int fiberIdentity ;
	float abscissa ;
	std::vector <float> positionVector  ;

	Eigen::VectorXf forceVector, velocityVector, movementDirVector ;

} Hand_t ;

#endif // HAND_H
