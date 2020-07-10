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

using namespace std;



int main()
{
	ifstream inputFileA; // declare input file to read
	//ofstream outputFileA; // declare output file to write

	inputFileA.open("link.txt");

	string contentString;

	// Test whether file opening was successful, and then do your stuff

	if(!inputFileA.fail() && inputFileA.is_open())
	{
		//do stuff while there is stuff to read in the file
		while( inputFileA >> contentString)
		{
			// cout << contentString << endl;
			break;
		}

		string lineString;
		while (getline(inputFileA, lineString))
		{
			// Check if line is content
			if (lineString.rfind("%", 0) != 0 && lineString != "% end") cout << lineString << endl;
		}


	}

	inputFileA.close();

}
