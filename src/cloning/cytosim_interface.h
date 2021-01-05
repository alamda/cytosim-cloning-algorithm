#ifndef CYTOSIM_INTERFACE_H
#define CYTOSIM_INTERFACE_H

#include "interface.h"

#include <string>

void set_interface(Interface & interface, std::string singularityPath, std::string cytosimContainerPath );

void exec_container(Interface & interface, std::string commandName) ;

void run_frametool(Interface & interface) ;

void run_sim(Interface & interface) ;

void run_report(Interface & interface) ;

#endif // CYTOSIM_INTERFACE
