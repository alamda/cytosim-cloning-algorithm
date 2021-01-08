#ifndef CLONING_LOGISTICS_H
#define CLONING_LOGISTICS_H

#include "cloning_params.h"
#include "iteration.h"

#include <vector>

int calc_total_num_clones_predicted(std::vector < int > vec) ;

int pick_clone(std::vector <int> vec) ;

void increment_up(std::vector < int > & vec) ;

void increment_down(std::vector <int> & vec) ;

void adjust_population(CloningParams & cloningParams, Iteration & iteration) ;


#endif // CLONING_LOGISTICS_H
