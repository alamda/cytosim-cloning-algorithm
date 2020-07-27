#include "simul.h"

// obtain simulation parameters from config.cym file
void get_simulation_params(Simulation & simul, std::string fileName)
{
	//simul.unloaded_speed
	std::regex rgx_unload("unloaded_speed");
	//simul.stall_force ;
	std::regex rgx_stall("stall_force");

	std::regex rgx_float("-?\\d+\\.?\\d*") ;

	// open file
	std::ifstream configFile(fileName.c_str());

	while (configFile)
	{
		std::string line ;

		while (std::getline(configFile, line))
		{
			std::smatch match_line ;
			std::smatch match_float ;

			if ( std::regex_search(line, match_line, rgx_unload) )
			{
				if ( std::regex_search(line, match_float, rgx_float))
					simul.unloaded_speed = std::stof(match_float.str(0));
			}
			else if ( std::regex_search(line, match_line, rgx_stall))
			{
				if (std::regex_search(line, match_float, rgx_float))
					simul.stall_force = std::stof(match_float.str(0));
			}
		}

		std::cout << "unloaded_speed: " << simul.unloaded_speed << std::endl ;
		std::cout << "stall_force: " << simul.stall_force << std::endl ;
	}
	configFile.close() ;
}
