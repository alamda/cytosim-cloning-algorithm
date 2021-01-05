#ifndef INTERFACE_H
#define INTERFACE_H

// data structure for paths for running external commands (like cytosim)

#include <string>

typedef struct Interface_s
{
	std::string singularityPath ;
	std::string cytosimContainerPath ;

} Interface ;

void set_interface(Interface & interface, std::string singularityPath, std::string cytosimContainerPath );

void exec_container(Interface & interface, std::string commandName) ;

void run_frametool(Interface & interface) ;

void run_sim(Interface & interface) ;

void calc_observable(std::string executableName) ;

#endif // INTERFACE_H
