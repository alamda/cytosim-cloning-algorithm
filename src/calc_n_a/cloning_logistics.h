#ifndef CLONING_LOGISTICS_H
#define CLONING_LOGISTICS_H

#include "cloning_params.h"
#include "iteration.h"
#include "clone.h"

#include <vector>

int calc_total_num_clones_predicted(std::vector < Clone > vec) ;

int pick_clone(std::vector <Clone> vec) ;

void increment_up(std::vector < Clone > & vec) ;

void increment_down(std::vector <Clone> & vec) ;

void adjust_population(CloningParams & cloningParams, Iteration & iteration) ;


#endif // CLONING_LOGISTICS_H
