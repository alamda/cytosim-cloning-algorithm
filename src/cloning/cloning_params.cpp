// parse the config.clone file with cloning algorithm parameters

#include "cloning_params.h"

#include <regex>
#include <string>
#include <fstream>

void get_cloning_params(CloningParams & cloningParams, std::string configFileName)
{
	// cloningParams.numClones
	std::regex rgxNumClones("n_clones") ;
	// cloningParams.numIters
	std::regex rgxNumIters("n_iters") ;
	// cloningParams.biasParam
	std::regex rgxBiasParam("bias_param") ;
	// cloningParams.iterLength
	std::regex rgxIterLength("iter_length") ;

	// Regex string for all kinds of numbers: positive and negative ints and floats
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

			if (std::regex_search(line, matchLine, rgxNumClones))
			{	// If line contains num clones string
				if (std::regex_search(line, matchNum, rgxNum))
					cloningParams.numClones = std::stoi(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxNumIters))
			{	// If line contains num iters string
				if (std::regex_search(line, matchNum, rgxNum))
					cloningParams.numIters = std::stoi(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxBiasParam))
			{	// If line contains bias param string
				if (std::regex_search(line, matchNum, rgxNum))
				cloningParams.biasParam = std::stof(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxIterLength))
			{	// If line contains iter length string
				if (std::regex_search(line, matchNum, rgxNum))
					cloningParams.iterLength = std::stof(matchNum.str(0)) ;
			}
		}
	}

	cloningParams.fullSimulLength = cloningParams.numIters * cloningParams.iterLength ;

	printf("cloningParams.biasParam:\t\t%f\n", cloningParams.biasParam) ;
	printf("cloningParams.numClones:\t\t%i\n", cloningParams.numClones) ;
	printf("cloningParams.numIters:\t\t%i\n", cloningParams.numIters) ;
	printf("cloningParams.iterLength:\t\t%f\ts\n", cloningParams.iterLength) ;
	printf("cloningParams.fullSimulLength:\t\t%f\ts\n", cloningParams.fullSimulLength) ;

	printf("\n") ;

	configFile.close() ;
}
