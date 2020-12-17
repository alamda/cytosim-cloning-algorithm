// data structure
// parameters of the cloning algorithm run, as read from config.clone input file

#ifndef CLONING_PARAMS_H
#define CLONING_PARAMS_H

#include <string>

typedef struct Clones_s
{
	// number of clones
	int numClones;

	// number of iterations
	int numIters ;

	// biasing parameter
	float biasParam ;

	// length of simulation for a single iteration, seconds
	float iterLength ;

} Clones ;

void get_cloning_params(Clones & clones, std::string configFileName) ;


#endif // CLONING_PARAMS_H
