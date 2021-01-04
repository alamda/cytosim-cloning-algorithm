// wrappers for calling cytosim executables

#include "cytosim_interface.h"

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>

void exec_container(std::string commandName)
{
	std::string commandPath = "/home/cytosim/bin/" ;
	commandPath.append(commandName) ;

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
	execl("/usr/bin/singularity", "singularity", "exec", "/home/alexandra/temp/singularity/cytosim_container/cytosim.sif", commandPath.c_str(), (char*)NULL);
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

void run_frametool()
{
	exec_container("frametool") ;
}

void run_sim()
{
	// call sim executable

	exec_container("sim2") ;
}

void run_report()
{
	// call the report executable

	exec_container("report2") ;
}
