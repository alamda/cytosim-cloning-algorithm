#include "clone.h"
#include "cloning_params.h"

#include <string>
#include <fstream>
#include <regex>
#include <cstdio>

void read_wDotIntegral(Clone & clone, std::string filename)
{
	std::regex rgxNum("-?\\d+\\.?\\d*") ;

	std::ifstream dataFile(filename.c_str()) ;

	// If wDotIntegral file was opened successfully
	while (dataFile)
	{
		// Declare empty string variable in which file line contents
		// will be temporariliy stored
		std::string line ;

		/* There's technically only one line in the file, but I am setting up
		 * the full regex line-by-line reading mechanism just in case/because
		 * I don't feel like changing it. There likely is a faster way of getting
		 * the single value out of the one-line file, but right now I'm mostly
		 * concerned about the whole cloning code working. This is a minor
		 * improvement that could be made but it is not high priority at the
		 * moment.
		 */

		while (std::getline(dataFile,line))
		{
			std::smatch matchNum ;

			if (std::regex_search(line, matchNum, rgxNum))
			{	// If line contains number
				clone.wDotIntegral = std::stof(matchNum.str(0)) ;
				printf("clone.wDotIntegral:\t\t\t%f\n", clone.wDotIntegral) ;
			}
		}

	}
}

void get_time_stamp(CloningParams & cloningParams, Clone & clone)
{
	clone.timeStamp = cloningParams.idxIter * cloningParams.iterLength ;

	printf("clone.timeStamp:\t\t\t%f\n", clone.timeStamp) ;
}
