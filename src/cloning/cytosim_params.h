/* Read the config.clone input file to change some
 * of the cloning param dependent Cytosim parameters.
 */

#ifndef CYTOSIM_PARAMS_H
#define CYTOSIM_PARAMS_H

#include "cloning_params.h"

#include <string>

typedef struct CytosimParams_s
{
	// values set by user
	float lenTimeStep ;
	float timePerFrame ;

	// Values from cloning algo
	float lenSimul ;

	// Values calculated using iteration length cloning param
	int numTimeSteps ;
	int numFrames ;
} CytosimParams ;

void get_cytosim_params(CytosimParams & cytosimParams, std::string configFileName) ;

void calculate_num_time_steps_and_frames(CytosimParams & cytosimParams, CloningParams & cloningParams) ;

bool exist_check(std::string path);

void gen_cytosim_config_file(CytosimParams & cytosimParams) ;

#endif // CYTOSIM_PARAMS_H
