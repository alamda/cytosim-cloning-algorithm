#ifndef SIMUL_H
#define SIMUL_H

/**	@brief Struct for containing simulation parameter data extracted from a *.cym config file.
	*/

#include <string>

typedef struct Simul_s
{
	float unloadedSpeed, stallForce ;

	float wDotIntegral ;

	float timeStepSize ;

	int dimension ;
	int numFrames ;
	int numSteps ;

} Simul ;

void get_simulation_params(Simul & simul, std::string fileName) ;

#endif // SIMUL_H
