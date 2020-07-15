/*
 * File I began writing to parse cytosim output files.
 *
 * Will try to avoid parsing output files by integrating cloning
 * with Cytosim code.
 *
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std; // considered bad practice (particularly in *.h files), avoid doing this
// see https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice

struct Frame
{
	std::string frame_number;
	std::string time;
	std::string data;
	std::string categories;
}

struct Linker
{
	// define a Linker class to cotain data extracted from output file
	// not done yet
	// see https://codereview.stackexchange.com/questions/38879/parsing-text-file-in-c
	std::string class;
	std::string identity;
	std::string fiber1;
	std::string abscissa1;
	std::string pos1;
	std::string fiber2;
	std::string abscissa2;
	std::string pos2;
	std::string force;
	std::string cos_angle;

}

int main()
{
	std::ifstream inputFileA; // declare input file to read
	//std::ofstream outputFileA; // declare output file to write

	inputFileA.open("link.txt");

	std::string contentString;

	// Test whether file opening was successful, and then do your stuff

	if(!inputFileA.fail() && inputFileA.is_open())
	{
		//do stuff while there is stuff to read in the file
		while( inputFileA >> contentString)
		{
			// std::cout << contentString << endl;
			break;
		}

		std::string lineString;
		while (getline(inputFileA, lineString))
		{
			// Check if line is content of interest
			if (lineString.rfind("%", 0) != 0 && lineString != "% end")
				std::cout << lineString << endl;
		}


	}

	inputFileA.close();

}
