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

	int n_a ;

	// float clone.timeStamp ;

	fs::directory_entry dirPath ;


} Clone ;

void read_wDotIntegral(Clone & clone, fs::path filePath) ;

// void get_time_stamp(CloningParams & cloningParams, Clone & clone) ;

#endif // CLONE_H
