// data structure
// parameters of the cloning algorithm run, as read from config.clone input file

#ifndef CLONING_PARAMS_H
#define CLONING_PARAMS_H

#include <string>

typedef struct CloningParams_s
{
	// number of clones
	int numClones;

	// number of iterations
	int numIters ;

	// biasing parameter
	float biasParam ;

	// length of simulation for a single iteration, seconds
	float iterLength ;

	// Index to count iterations
	int idxIter = 0;

	float fullSimulLength ;

} CloningParams ;

void get_cloning_params(CloningParams & cloningParams, std::string configFileName) ;


#endif // CLONING_PARAMS_H
