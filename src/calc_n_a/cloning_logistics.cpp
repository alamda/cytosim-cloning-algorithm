/* Generate a data structure containing information on which clones are duplicated
 * and to which directory.
 * Also need to make sure total number of clones is correct.
 * determines logistics for which clones are deleted/replicated
 */

#include "cloning_logistics.h"
#include "cloning_params.h"
#include "iteration.h"
#include "clone.h"

#include <random>
#include <numeric>	// std::accumulate()
#include <vector>


int calc_total_num_clones_predicted(std::vector < Clone > vec)
{
	// http://www.cplusplus.com/reference/numeric/accumulate/
	// https://stackoverflow.com/a/52685486

	int numClones = 0 ;

	for (Clone & clone : vec)
	{
		numClones+=clone.n_a ;
	}
	return numClones;
}

int pick_clone(std::vector <Clone> vec)
{

	// https://stackoverflow.com/a/19728404
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0,vec.size()); // guaranteed unbiased

	return uni(rng);
}

void increment_up(std::vector < Clone > & vec)
{
	int cloneIdx = pick_clone(vec) ;


	vec[cloneIdx].n_a++ ;

	printf("Incremented up clone number %i\n", cloneIdx) ;

}

void increment_down(std::vector < Clone > & vec)
{
	int cloneIdx = pick_clone(vec) ;

	while (vec[cloneIdx].n_a == 0)
	{
		int cloneIdx = pick_clone(vec) ;
	}



	vec[cloneIdx].n_a-- ;

	printf("Incremented down clone number %i\n", cloneIdx) ;
}

void adjust_population(CloningParams & cloningParams, Iteration & iteration)
{
	iteration.numClonesPredicted = calc_total_num_clones_predicted(iteration.cloneVector) ;

	printf("iteration.numClonesPredicted:\t%d\n", iteration.numClonesPredicted) ;

	while (iteration.numClonesPredicted != cloningParams.numClones)
	{
		int diff = iteration.numClonesPredicted - cloningParams.numClones ;

		printf("Difference between current number of clones and required number of clones: %i\n", diff) ;

		if (diff < 0)
		{
			for (int idx = 0; idx<abs(diff); ++idx)
			{
				increment_up(iteration.cloneVector) ;
			}
		}
		else
		{
			for (int idx = 0; idx<abs(diff) ; ++idx)
			{
				increment_down(iteration.cloneVector) ;
			}
		}

		iteration.numClonesPredicted = calc_total_num_clones_predicted(iteration.cloneVector) ;

		printf("iteration.numClonesPredicted (Adjustment in progress): %i\n", iteration.numClonesPredicted) ;
	}

	printf("iteration.numClonesPredicted (After adjustment): %d\n", iteration.numClonesPredicted) ;

}


void build_clone_list()
{

}

void generate_logistics()
{

}

void check_population()
{
 // check whether the total number of clones matches the input file param
 // add up all clones
 // if too large, randomly decrease clone numbers by one until matches
 // if too small, randomly increase clone numbers by one until matches
 // (including clones that were originally going to be deleted)
}
