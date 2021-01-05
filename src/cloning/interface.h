#ifndef INTERFACE_H
#define INTERFACE_H

// data structure for paths for running external commands (like cytosim)

#include <string>

typedef struct Interface_s
{
	std::string singularityPath ;
	std::string cytosimContainerPath ;
	
} Interface ;

#endif // INTERFACE_H
