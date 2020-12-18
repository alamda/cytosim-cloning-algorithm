// parse the config.clone file with some of the cytosim parameters

#include "cytosim_params.h"
#include "cloning_params.h"

#include <regex>
#include <string>
#include <fstream>
#include <math.h>		/* ceil */

void get_cytosim_params(Cytosim & cytosim, std::string configFileName)
{
	// cytosim.lenTimeStep
	std::regex rgxLenTimeStep("time_step_len");
	// cytosim.timePerFrame
	std::regex rgxTimePerFrame("time_per_frame") ;

	// Regex string for all kinds of numbers
	std::regex rgxNum("-?\\d+\\.?\\d*") ;

	// Open cloning configuration file
	std::ifstream configFile(configFileName.c_str()) ;

	// If configuration file was opened successfully
	while (configFile)
	{
		// Declare empty string variable in which file line
		// contents will be temporarily stored
		std::string line ;

		// Read config file line-by-line
		while (std::getline(configFile, line))
		{
			std::smatch matchLine ;
			std::smatch matchNum ;

			if (std::regex_search(line, matchLine, rgxLenTimeStep))
			{	// If line contains time step length
				if (std::regex_search(line, matchNum, rgxNum))
					cytosim.lenTimeStep
					 = std::stof(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxTimePerFrame))
			{	// If line contains time per frame
				if (std::regex_search(line, matchNum, rgxNum))
					cytosim.timePerFrame = std::stof(matchNum.str(0)) ;
			}
		} // end while loop
	} // end while loop

	printf("cytosim.lenTimeStep:\t\t%f\n", cytosim.lenTimeStep) ;
	printf("cytosim.timePerFrame:\t\t%f\n", cytosim.timePerFrame) ;

	configFile.close() ;
}

void calculate_num_time_steps_and_frames(Cytosim & cytosim, Clones & clones)
{
	cytosim.numTimeStep = static_cast<int>( ceil( clones.iterLength / cytosim.lenTimeStep ) ) ;

	cytosim.numFrames = static_cast<int>( ceil (clones.iterLength / cytosim.timePerFrame) ) ;

	printf("cytosim.numTimeStep:\t%i\n", cytosim.numTimeStep) ;
	printf("cytosim.numFrames:\t%i\n", cytosim.numFrames) ;
}
