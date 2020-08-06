#include "frame.h"
#include "simul.h"
#include "parser.h"
#include "calculator.h"

#include <string>



int main()
{
	Simul simul ;

	const std::string paramFileName = "config.cym";

	get_simulation_params(simul, paramFileName) ;
	simul.wDotIntegral = 0.0 ;

	// Name of data file to be read:
	const std::string dataFileName = "link.txt";
	const std::string wDotOutputFileName = "wDots.txt" ;
	const std::string wDotIntegralFileName = "wDotIntegral.txt" ;

	get_output_file_contents(simul, dataFileName, wDotOutputFileName, wDotIntegralFileName);

	return 0;
}
