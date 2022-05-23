#ifndef SIMUL_H
#define SIMUL_H

/**	@brief Struct for containing simulation parameter data extracted from a *.cym config file.
	*/

#include <string>
#include <vector>
#include "couple_prop.h"

typedef struct Simul_s
{

	float stallForce ;
	float unloadedSpeed ;

	float observableIntegral ;

	float timeStepSize ;

	int dimension ;
	int numFrames ;
	int numSteps ;

	float duration ;

	std::vector < Couple_Prop > couplePropVec ;
	std::vector < Hand_Prop > handPropVec ;

} Simul ;

void get_simulation_params(Simul & simul, std::string configFileName) ;

void get_object_props(Simul & simul, std::string propFileName) ;

#endif // SIMUL_H
