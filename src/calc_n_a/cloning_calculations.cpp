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
#include <random> // for safe generation of random numbers



void calc_s_a(CloningParams & cloningParams, Clone & clone)
{
// takes wDotIntegral.txt as input
// extracts integral value
// needs to know biasing parameter h from the cloning configuration file

	clone.s_a = exp(cloningParams.biasParam  * clone.wDotIntegral) ;

	printf("clone.s_a:\t\t%f\n", clone.s_a);
}
//
// void calc_s_a(CloningParams & cloningParams, Clone & currentClone, Clone & pastClone)
// {
// // needs to know exponential value from clone's previous iteration
// // s_a = calc_exp_now/calc_exp_previous
//
// 	calc_exponential(cloningParams, currentClone) ;
// 	printf("currentClone.expObservable:\t\t%f\n", currentClone.expObservable) ;
// 	calc_exponential(cloningParams, pastClone) ;
// 	printf("pastClone.expObservable:\t\t%f\n", pastClone.expObservable) ;
//
// 	currentClone.s_a = currentClone.expObservable / pastClone.expObservable ;
// 	printf("currentClone.s_a:\t\t\t%f\n", currentClone.s_a) ;
// }

void sum_s_a(Iteration & iteration, Clone & clone)
{
	iteration.sum_s_a += clone.s_a ;
}

float gen_noise()
{
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	//define function that generates a float uniformly distributed on [0,1] (both inclusive)
	std::uniform_real_distribution<> dis(0.0, std::nextafter(1.0, std::numeric_limits<float>::max()));

	return dis(gen) ;
}


void calc_n_a(CloningParams & cloningParams, Iteration & iteration, Clone & clone)
{
// needs to know N_c (total number of clones) from cloning config file
// generate random number between 0 and 1
// needs to STORE the calculated values of n_a

	float noiseTerm = gen_noise() ;

	// printf("noise term: %f\n", noiseTerm) ;

	clone.n_a = static_cast <int>(floor(clone.s_a * cloningParams.numClones / iteration.sum_s_a + noiseTerm)) ;

	iteration.numClonesPredicted += clone.n_a ;

	// printf("clone.n_a: %d\n", clone.n_a) ;



}
