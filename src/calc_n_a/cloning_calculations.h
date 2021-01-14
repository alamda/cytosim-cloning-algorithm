#ifndef CLONING_CALCULATIONS_H
#define CLONING_CALCULATIONS_H

#include "clone.h"
#include "cloning_params.h"
#include "iteration.h"

#include <string>


// void calc_exponential(CloningParams & cloningParams, Clone & clone) ;

void calc_s_a(CloningParams & cloningParams, Clone & clone) ;

void sum_s_a(Iteration & iteration, Clone & clone) ;

float gen_noise() ;

void calc_n_a(CloningParams & cloningParams, Iteration & iteration, Clone & clone) ;


#endif // CLONING_CALCULATIONS_H
