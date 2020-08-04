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
	std::vector <float> positionVector_std  ;

	Eigen::VectorXf positionVector_eigen ;

	std::vector <float> directionVector_std ;

	Eigen::VectorXf directionVector_eigen ;
	// Eigen::Vector3f directionVector3D_eigen ;

	Eigen::VectorXf forceVector, velocityVector;

} Hand ;

#endif // HAND_H
