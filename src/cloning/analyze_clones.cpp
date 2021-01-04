/* Iterate over directories and read wDotINtegral.txt values
 * Calculate s_a for each clone (need to store previous value)
 * Calculate sum of s_a for all clones
 *
 * Start new iteration
 * Calculate n_a for each clone
 */
#include "analyze_clones.h"

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void calc_observable()
{
	// calls the calculate executable to calculate wdot from the cytosim ouput data

	// https://stackoverflow.com/a/13558040

	// Create child process to run calculate executable
	pid_t pid = fork() ;
	int status ;

	switch (pid)
	{
	case -1: //error
		perror("fork") ;
		exit(1) ;

	case 0: // child process
	// https://stackoverflow.com/a/20509563
	// run the calculate executable
	execl("calculate", "calculate", (char*)NULL);
	// execl doesn't return unless there is a problem
	perror("execl");
	exit(1);

	default: // parent process, pid now contains the child pid
		// wait for child to complete
		while (-1 == waitpid(pid, &status, 0)) ;
		 	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
			{
				std::cerr << "process (pid=" << pid << ") failed" << std::endl ;
			}
		break ;
	}
}

void calc_exponential()
{
// takes wDotIntegral.txt as input
// extracts time stamp and integral value
// needs to know biasing parameter h from the cloning configuration file
}

void calc_s_a()
{
// needs to know exponential value from clone's previous iteration
// s_a = calc_exp_now/calc_exp_previous
}

void sum_s_a()
{
// sum of s_a values for all clones in the iteration
}

void calc_n_a()
{
// needs to know N_c (total number of clones) from cloning config file
// generate random number between 0 and 1
// needs to STORE the calculated values of n_a
}
