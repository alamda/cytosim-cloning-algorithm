#ifndef FIBER_H
#define FIBER_H

#include <vector>

#include "Eigen/Dense"

/**	@brief Struct for containing information of a linker with two hands.

	*/

typedef struct Fiber_s
{
	int fiberIdentity ;

	Eigen::VectorXf forceVector_eigen ;

	Eigen::VectorXf directionVector_eigen ;
	// Axial force
	float observable = 0.0;
} Fiber ;

#endif // FIBER_H
