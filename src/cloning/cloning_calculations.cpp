/* Iterate over directories and read wDotINtegral.txt values
 * Calculate s_a for each clone (need to store previous value)
 * Calculate sum of s_a for all clones
 *
 * Start new iteration
 * Calculate n_a for each clone
 */
#include "cloning_calculations.h"

#include <string>
#include <fstream>
#include <regex>

void read_wDotIntegral(std::string filename)
{
	std::regex rgxNum("-?\\d+\\.?\\d*") ;

	std::ifstream file(filename.c_str()) ;

	// If wDotIntegral file was opened successfully
	while file
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

		while (std::getline(configFile,line))
		{
			std::smatch matchNum ;

			if (std::regex_search(line,))
			{	// If line contains number
				
			}
		}

	}
}

void calc_exponential()
{
// takes wDotIntegral.txt as input
// extracts time stamp and integral value
// needs to know biasing parameter h from the cloning configuration file
}

void calc_s_a()
{
// needs to know exponential value from clone's previous iteration
// s_a = calc_exp_now/calc_exp_previous
}

void sum_s_a()
{
// sum of s_a values for all clones in the iteration
}

void calc_n_a()
{
// needs to know N_c (total number of clones) from cloning config file
// generate random number between 0 and 1
// needs to STORE the calculated values of n_a
}
