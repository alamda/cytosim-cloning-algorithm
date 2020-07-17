/*
 * File I began writing to parse cytosim output files.
 *
 * Will try to avoid parsing output files by integrating cloning
 * with Cytosim code.
 *
 */


#include <cstdio>

// Define a constant for the max buffer size
constexpr int maxstr = 1024 ;

int main()
{
	char buffer[maxstr] ; // define a buffer

	FILE * file_reference = fopen("link.txt", "r");

	while(fgets( buffer, maxstr, file_reference ))
	{
		fputs(buffer, stdout);
	}

	fclose(file_reference);
}
