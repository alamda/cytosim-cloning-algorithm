/*
 * Some basic test code for launching cytosim simulations
 * Not fully integrated, just some stuff I wrote while brainstorming
 *
 */

#include "launch.h"

#include <fstream>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
	printf("Prior to launching clones, make sure the following files are in the current directory:\n \tconfig.cym\n \tcytosim.sbatch\n \tsim (Cytosim executable)\n \treport (Cytosim executable)\n \tframetool (Cytosim executable)\n \n");
	int N_clones ;

	if (argc > 1)
	{
		N_clones = atoi(argv[1]) ;
	}
	else
	{
		std::string inputString ;
		printf("Enter number of clones to launch: ");
		std::cin >> inputString ;
		N_clones = std::stoi(inputString) ;
	}

	launch_simulations(N_clones) ;


	return 0;
}

void launch_simulations(int & N_clones) // seems to be done?
{
	/*
	 * ✓ create separate directories
	 * ✓ copies config.cym and cytosim.sbatch files
	 * ✓ starts cytosim simulation via sbatch
	 */

	char buffer[255];

	for (int i=0; i<N_clones; i++)
	{
		// Create string of shell commands and run the commands
		std::sprintf(buffer, "mkdir -p sims/%03d; cp sim report frametool config.cym cytosim.sbatch sims/%03d; cd sims/%03d; pwd; sbatch cytosim.sbatch", i, i, i);
		printf("%s\n", buffer) ;
		// system(buffer);
	}
}

bool checkForFiles()
{
// write function to check that the appropriate files are present

return true ;
}
