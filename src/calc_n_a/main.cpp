#include "cloning_params.h"
#include "iteration.h"
#include "clone.h"
#include "cloning_calculations.h"
#include "cloning_logistics.h"

#include <filesystem>
namespace fs = std::filesystem ;
#include <iostream> // std::cout
#include <typeinfo>
#include <fstream>

int main()
{
	/* Read input file specifying cloning parameters
	 * (cloning_params.cpp)
	 */

	// Define the name of the cloning config file
	const std::string cloneConfigFileName = "config.clone" ;

	// Declare cloning struct and get params
	CloningParams cloningParams ;

	get_cloning_params(cloningParams, cloneConfigFileName) ;

	/* Initialize Iteration data struct to store interesting numbers */
	Iteration iteration ;

	fs::path rootPath = fs::current_path() ;

	std::cout << "S_m:\t" << iteration.sum_s_a << std::endl ;


	/* Iterate over subdirectories (one subdirectory per clone) */

	// https://www.bfilipek.com/2019/04/dir-iterate.html#using-c17

	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		const auto filenameStr = entry.path().filename().string();

		if (entry.is_directory())
		{
			/* Initialize clone data struct */

			// std::cout << typeid(filenameStr).name() << std::endl ;

			Clone clone ;

			clone.dirPath = entry ;
			clone.dirName = filenameStr ;

			fs::current_path(entry) ;

			/* Read observable_integral.txt (clone.cpp) */

			// std::cout << fs::current_path() << std::endl ;

			const std::string wDotIntFileName = "observable_integral.txt" ;

			read_observable_integral(clone, wDotIntFileName) ;

			// std::cout << clone.observable_integral << std::endl  ;

			/* Calculate s_a for clone (cloning_calculations.cpp) */

			calc_s_a(cloningParams, clone) ;

			// std::cout << clone.s_a << std::endl ;

			iteration.cloneVector.push_back(clone) ;

			/* Add clone's s_a value to sum_s_a (cloning_calculations.cpp) */

			sum_s_a(iteration, clone) ;

			std::cout << std::endl ;
		}

	}

	std::cout << "S_m:\t" << iteration.sum_s_a << std::endl ;

	// Write iteration.sum_s_a (also known as S_m) to file

	fs::current_path(rootPath) ;

	std::string SmFileName = "S_m.txt" ;

	std::ofstream SmFile(SmFileName.c_str()) ;

	SmFile << iteration.sum_s_a ;

	SmFile.close() ;

	/* Iterate over clones again */

	/* Calculate n_a for each clone */
	for (Clone & clone : iteration.cloneVector)
	{

		// Calculate n_a, the number of duplicates for each clone
		calc_n_a(cloningParams, iteration, clone) ;

		// std::cout << clone.n_a << " " ;

		// Add the number of duplicates for the clone to the genealogy vector
		// iteration.genealogy.push_back(clone.n_a) ;

	}

	// std::cout << std::endl ;


	// for (Clone & clone : iteration.cloneVector)
	// {
	// 	std::cout << clone.n_a << " " ;
	// }
	//
	// std::cout << std::endl ;

	/* Adjust the population so the total number of of clones matches the value specified in clone.config */
	adjust_population(cloningParams, iteration) ;

	// for (Clone & clone : iteration.cloneVector)
	// {
	// 	std::cout << clone.n_a << " " ;
	// }
	//
	// std::cout << std::endl ;


	/* Write clone ID and corresponding n_a to file */

	fs::current_path(rootPath) ;

	std::string genealogyFileName = "genealogy.txt" ;

	std::ofstream genealogyFile(genealogyFileName.c_str()) ;

	/* Calculate n_a for each clone */
	for (Clone & clone : iteration.cloneVector)
	{
		genealogyFile << clone.dirName ;
		genealogyFile << "\t" ;
		genealogyFile << clone.n_a ;
		genealogyFile << "\n" ;
	}

	genealogyFile.close() ;

}
