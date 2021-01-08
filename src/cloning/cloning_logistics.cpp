/* Generate a data structure containing information on which clones are duplicated
 * and to which directory.
 * Also need to make sure total number of clones is correct.
 * determines logistics for which clones are deleted/replicated
 */

#include "cloning_logistics.h"
#include "cloning_params.h"
#include "iteration.h"

#include <random>
#include <numeric>	// std::accumulate()
#include <vector>


int calc_total_num_clones_predicted(std::vector < int > vec)
{
	// http://www.cplusplus.com/reference/numeric/accumulate/
	// https://stackoverflow.com/a/52685486
	return std::accumulate(vec.begin(), vec.end() , 0) ;
}

int pick_clone(std::vector <int> vec)
{

	// https://stackoverflow.com/a/19728404
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0,vec.size()); // guaranteed unbiased

	return uni(rng);
}

void increment_up(std::vector < int > & vec)
{
	int cloneIdx = pick_clone(vec) ;

	vec[cloneIdx]++ ;
}

void increment_down(std::vector < int > & vec)
{
	int cloneIdx = pick_clone(vec) ;

	while (vec[cloneIdx] == 0)
	{
		cloneIdx = pick_clone(vec) ;
	}

	vec[cloneIdx]-- ;
}

void adjust_population(CloningParams & cloningParams, Iteration & iteration)
{
	iteration.numClonesPredicted = calc_total_num_clones_predicted(iteration.genealogy) ;

	printf("iteration.numClonesPredicted:\t%d\n", iteration.numClonesPredicted) ;

	while (iteration.numClonesPredicted != cloningParams.numClones)
	{
		int diff = iteration.numClonesPredicted - cloningParams.numClones ;

		if (diff < 0)
		{
			for (int idx = 0; idx<abs(diff); ++idx)
			{
				increment_up(iteration.genealogy) ;
			}
		}
		else
		{
			for (int idx = 0; idx<abs(diff) ; ++idx)
			{
				increment_down(iteration.genealogy) ;
			}
		}

		iteration.numClonesPredicted = calc_total_num_clones_predicted(iteration.genealogy) ;
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
