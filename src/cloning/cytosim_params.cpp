// parse the config.clone file with some of the cytosim parameters

#include "cytosim_params.h"
#include "cloning_params.h"

#include <regex>
#include <string>
#include <fstream>
#include <math.h>		/* ceil */
// Note: filesystem is not available for C++11, need to use
// C++17, which is set in the main CMakeLists.txt
#include <filesystem>	// std::filesystem

namespace fs = std::filesystem;

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

	printf("cytosim.lenTimeStep:\t\t%f\ts\n", cytosim.lenTimeStep) ;
	printf("cytosim.timePerFrame:\t\t%f\ts\n", cytosim.timePerFrame) ;
	printf("\n") ;

	configFile.close() ;
}

void calculate_num_time_steps_and_frames(Cytosim & cytosim, Clones & clones)
{

	cytosim.numTimeSteps = static_cast<int>( ceil( clones.iterLength / cytosim.lenTimeStep ) ) ;

	cytosim.numFrames = static_cast<int>( ceil (clones.iterLength / cytosim.timePerFrame) ) ;

	cytosim.lenSimul = clones.iterLength ;


	printf("cytosim.numTimeStep:\t\t%i\n", cytosim.numTimeSteps) ;
	printf("cytosim.numFrames:\t\t%i\n", cytosim.numFrames) ;
	printf("cytosim.lenSimul:\t\t%f\ts\n", cytosim.lenSimul) ;

	printf("\n") ;
}

bool exist_check(std::string path)
{
	fs::file_status s = fs::file_status{} ;

	return fs::status_known(s) ? fs::exists(s) : fs::exists(path) ;
}

void gen_cytosim_config_file(Cytosim & cytosim)
{
	// check for the directory containing precursor *.cym files, return error and exit if not found
	// https://en.cppreference.com/w/cpp/filesystem/exists
	if (exist_check("cym.d") &&
		exist_check("cym.d/simul.cym") &&
	 	exist_check("cym.d/space.cym") &&
		exist_check("cym.d/objects.cym") &&
		exist_check("cym.d/report.cym")
		)
	{
		// define edits to files

		char simulEditBuff [100] ;
		int simulEditLen = sprintf(simulEditBuff, "change system\n{\n\ttime_step = %f ;\n}\n\n", cytosim.lenTimeStep) ;

		char runEditBuff [100] ;
		int runEditLen = sprintf(runEditBuff, "run system \n{\n\tduration = %f ;\n\t nb_frames = %i ; \n}\n\n", cytosim.lenSimul, cytosim.numFrames) ;

		// concatenate precursor files and edits into config.cym
		// simul.cym  simul_edit space.cym objects.cym run_edit report.cym > config.cym
		std::ifstream if_simul("cym.d/simul.cym", std::ios_base::binary);
		std::ifstream if_space("cym.d/space.cym", std::ios_base::binary);
		std::ifstream if_objects("cym.d/objects.cym", std::ios_base::binary);
		std::ifstream if_report("cym.d/report.cym", std::ios_base::binary) ;
		std::ofstream of_config("config.cym", std::ios_base::binary);

		of_config << if_simul.rdbuf() << simulEditBuff
				  << if_space.rdbuf()
				  << if_objects.rdbuf()
				  << runEditBuff
				  << if_report.rdbuf() ;

	}
	else
	{
		printf("one or more of the required precursor files is missing in cym.d\n") ;
		printf("required precursor files: simul.cym, space.cym, objects.cym, run.cym\n") ;

		printf("\nTerminating program\n") ;

		exit(1);
	}
}
