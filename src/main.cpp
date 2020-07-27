#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <iterator>
#include "Eigen/Dense"
#include <climits>
#include "parse.h"
#include "calculate.h"

std::string Frame::frameStr = "frame";
std::string Frame::timeStr = "time";
std::string Frame::reportStr = "report";
std::string Frame::categoriesStr = "class";
std::string Frame::endStr = "end";

int main()
{
	Simulation simul ;

	const std::string paramFileName = "config.cym";

	get_simulation_params(simul, paramFileName) ;

	// Name of data file to be read:
	const std::string dataFileName = "link.txt";

	get_output_file_contents(dataFileName, simul);

	return 0;
}