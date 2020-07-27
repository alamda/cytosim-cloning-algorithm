#ifndef SIMUL_H
#define SIMUL_H

#include <cstdio>
#include <string>

typedef struct Simulation
{
	float unloaded_speed, stall_force ;
} Simulation_t ;

void get_simulation_params(Simulation & simul, std::string fileName)

#endif // SIMUL_H
