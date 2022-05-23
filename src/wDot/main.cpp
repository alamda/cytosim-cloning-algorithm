#include "frame.h"
#include "simul.h"
#include "parser.h"
#include "calculator.h"

#include <string>



int main()
{
	// Declare simulation object
	Simul simul ;

	// Define the name of the Cytosim config file
	const std::string configFileName = "config.cym";

	// Define the name of the object property file
	// (output of `report property`, property.txt)
	const std::string propFileName = "property.txt" ;

	get_simulation_params(simul, configFileName ) ;

	// this function was part of the first few steps to differentiating
	// between passive and active cross-linkers. temporarily commenting out.
	// get_object_props(simul, propFileName) ;

	// Set integral for the trajectory to zero, will be adding to it later
	simul.observableIntegral = 0.0 ;

	// Name of data file to be read:
	const std::string dataFileName = "link.txt";

	// Name of output files:
	const std::string observableOutputFileName = "wDots.txt" ;
	const std::string observableIntegralFileName = "observable_integral.txt" ;

	// Do the Thing
	process_data_file(simul, dataFileName, observableOutputFileName, observableIntegralFileName);

	return 0;
}
