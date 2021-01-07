/* Iterate over directories and read wDotINtegral.txt values
 * Calculate s_a for each clone (need to store previous value)
 * Calculate sum of s_a for all clones
 *
 * Start new iteration
 * Calculate n_a for each clone
 */
#include "cloning_calculations.h"
#include "clone.h"

#include <string>
#include <fstream>
#include <regex>
#include <cstdio>
#include <math.h> // exp, floor



void calc_exponential(CloningParams & cloningParams, Clone & clone)
{
// takes wDotIntegral.txt as input
// extracts time stamp and integral value
// needs to know biasing parameter h from the cloning configuration file

	clone.expObservable = exp(cloningParams.biasParam * clone.timeStamp * clone.wDotIntegral) ;
}

void calc_s_a(CloningParams & cloningParams, Clone & currentClone, Clone & pastClone)
{
// needs to know exponential value from clone's previous iteration
// s_a = calc_exp_now/calc_exp_previous

	calc_exponential(cloningParams, currentClone) ;
	printf("currentClone.expObservable:\t\t%f\n", currentClone.expObservable) ;
	calc_exponential(cloningParams, pastClone) ;
	printf("pastClone.expObservable:\t\t%f\n", pastClone.expObservable) ;

	currentClone.s_a = currentClone.expObservable / pastClone.expObservable ;
	printf("currentClone.s_a:\t\t\t%f\n", currentClone.s_a) ;
}

void sum_s_a(Iteration & iteration, Clone & clone)
{
	iteration.sumOfExponentials += clone.expObservable ;
}

void calc_n_a(CloningParams & cloningParams, Iteration & iteration, Clone & clone)
{
// needs to know N_c (total number of clones) from cloning config file
// generate random number between 0 and 1
// needs to STORE the calculated values of n_a

	// TODO: need to add random number between 0 and 1 (instead of 0.0)

	iteration.numDuplications = static_cast <int>(floor(clone.s_a * cloningParams.numClones / iteration.sumOfExponentials + 0.0)) ;
}
