#ifndef CLONE_H
#define CLONE_H

#include "cloning_params.h"

#include <string>

// Data structure to store info for an individual clone

typedef struct Clone_s
{
	float wDotIntegral = 0.0 ;

	float timeStamp  = 0.0 ;

	float expObservable ;

	float s_a ; 


} Clone ;

void read_wDotIntegral(Clone & clone, std::string filename) ;

void get_time_stamp(CloningParams & cloningParams, Clone & clone) ;

#endif // CLONE_H
