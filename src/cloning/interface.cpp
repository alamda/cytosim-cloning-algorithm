// wrappers for calling cytosim executables

#include "interface.h"

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fcntl.h>

void set_interface(Interface & interface, std::string singularityPath, std::string cytosimContainerPath)
{
	interface.singularityPath = singularityPath ;
	interface.cytosimContainerPath = cytosimContainerPath ;

	printf("interface.singularityPath = %s\n", interface.singularityPath.c_str()) ;
	printf("interface.cytosimContainerPath = %s\n", interface.cytosimContainerPath.c_str()) ;

	printf("\n") ;
}

void exec_container(Interface & interface, const char** argv)
{
	// https://stackoverflow.com/a/13558040
	// Create child process to run calculate executable
	pid_t pid = fork() ;
	int status ;

	switch (pid)
	{
		case -1: //error
		{
			perror("fork") ;
			exit(1) ;
		}

		case 0: // child process
		{
			// https://stackoverflow.com/a/20509563
			// run the command
			const char * strMatch = strstr(argv[3], "report");

			// if the command is the report command, write output to file
			if (strMatch != NULL )
			{
				// https://pubs.opengroup.org/onlinepubs/009604499/basedefs/fcntl.h.html

				// printf("%s\n", argv[3]) ;

				// open the file link.txt for writing stdout
				int out = open("link.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				dup2(out, 1); // replace standard output with output file

				// run the cytosim command
				execv(interface.singularityPath.c_str(), (char * const *) argv);

				close(out) ;
			}
			else
			{	// otherwise just run the command without piping the output to a file
				execv(interface.singularityPath.c_str(), (char * const *) argv);
			}

			exit(1);
		}
		default: // parent process, pid now contains the child pid
		{
			// wait for child to complete
			while (-1 == waitpid(pid, &status, 0)) ;
			 	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
				{
					std::cerr << "process (pid=" << pid << ") failed" << std::endl ;
				}
			break ;
		}
	}
}

void run_frametool(Interface & interface)
{
	const char* argv[] = {"singularity", "exec", interface.cytosimContainerPath.c_str(), "/home/cytosim/bin/frametool", NULL} ;
	exec_container(interface,  argv) ;
}

void run_sim(Interface & interface)
{
	// call sim executable
	const char* argv[] = {"singularity", "exec", interface.cytosimContainerPath.c_str(), "/home/cytosim/bin/sim2", NULL} ;
	exec_container(interface,  argv);
}

void run_report(Interface & interface)
{
	// call report executable
	const char* argv[] = {"singularity", "exec", interface.cytosimContainerPath.c_str(), "/home/cytosim/bin/report2", "couple:link", NULL} ;
	exec_container(interface, argv) ;
}

void calc_observable(std::string executableName)
{
	// calls the calculate executable to calculate wdot from the cytosim ouput data

	// https://stackoverflow.com/a/13558040

	// Create child process to run calculate executable
	pid_t pid = fork() ;
	int status ;

	switch (pid)
	{
		case -1: //error
		{
			perror("fork") ;
			exit(1) ;
		}

		case 0: // child process
		{
			// https://stackoverflow.com/a/20509563
			// run the calculate executable
			execl(executableName.c_str(), executableName.c_str(), (char*)NULL);
			// execl doesn't return unless there is a problem
			perror("execl");
			exit(1);
		}

		default: // parent process, pid now contains the child pid
		{	// wait for child to complete
			while (-1 == waitpid(pid, &status, 0)) ;
			 	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
				{
					std::cerr << "process (pid=" << pid << ") failed" << std::endl ;
				}
			break ;
		}
	}
}
