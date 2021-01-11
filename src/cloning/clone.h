#ifndef CLONE_H
#define CLONE_H

#include "cloning_params.h"

#include <string>
#include <filesystem>
namespace fs = std::filesystem ;

// Data structure to store info for an individual clone

typedef struct Clone_s
{
	std::string dirName ;

	float wDotIntegral = 0.0 ;

	float s_a ;

	int numDuplicates ;

	// float clone.timeStamp ;

	fs::path dirPath ;


} Clone ;

void read_wDotIntegral(Clone & clone, std::string filename) ;

// void get_time_stamp(CloningParams & cloningParams, Clone & clone) ;

#endif // CLONE_H
