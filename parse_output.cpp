#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include "parse_output.h"

struct Frame
{
	int frameNumber ;
	const std::string frameStr = "frame";

	float timeStamp ;
	const std::string timeStr = "time";

	std::string reportCommand ;
	const std::string reportStr = "report";

	std::string dataCategories ;
	const std::string categoriesStr = "class";

	std::vector <std::string> dataLines ;
};

void process_line(std::string line, Frame & frame)
{
	std::smatch match ;

	if (line.find(frame.frameStr) != std::string::npos)
	{
		std::regex rgx("[0-9]+");

		if (std::regex_search(line, match, rgx))
		{
			frame.frameNumber =  std::stoi(match.str(0));
		}
	}
	else if (line.find(frame.timeStr) != std::string::npos)
	{
		std::regex rgx("[0-9]+.[0-9]+");

		if (std::regex_search(line, match, rgx))
		{
			frame.timeStamp =  std::stof(match.str(0));
			printf("%s\n", line);
			printf("%d\n", frame.timeStamp);
		}
	}
	// else if ()
	// {
	// 	// Extract string with report command used to generate data file
	// }
	// else if ()
	// {
	// 	// Extract string with category names of data in file
	// }
	// else if ()
	// {
	// 	// Extract vector of strings of data lines for the frame
	// }


}

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
 void get_file_contents( std::string fileName,
						std::string const startSubstring,
						std::string const endString,
						std::vector <std::vector <std::string> > & vectorOfFrames,
						std::vector <Frame> & vectorOfFrameObjects )
{
	// open file
	std::ifstream dataFile(fileName.c_str());

	// define vector for storing content of a single frames
	std::vector <std::string> vectorOfFrameContent;

	while (dataFile)
	{
		// Define string variable
		std::string line ;
		int frameNumber = 0;

		// Read line by line and sort into frames
		while (std::getline(dataFile, line))
		{
			std::size_t found_end ;
			std::size_t found_start ;

			found_end = line.find(endString);

			// If the line does not match endString
			if(found_end = std::string::npos)
			{
				// check if the line contains the string denoting the start of the frame
				found_start = line.find(startSubstring);

				// if start substring is found in the line
				if (found_start != std::string::npos)
				{
					// Create new frame object
					Frame frame; // needs to be available to other scopes
					//would like to initialize object in this scope tho

					printf("start of frame %d, frame object created\n", frameNumber);
				}

				process_line(line, frame);


				if (found_end != std::string::npos)
				{
					// will remove vector of frames
					vectorOfFrameObjects.push_back(frame);

					printf("end of frame %d, pushing back frame objects to vector", frameNumber);

					frameNumber++ ;

					if (frameNumber > 1)
					{
						// do calculations on two adjacent frames
					}
				}
			}
		}
	printf("Total number of frames: %d\n", frameNumber);
	}

	//Close The File
	dataFile.close();
}

int main()
{
	// Name of data file to be read:
	const std::string fileName = "link.txt";
	const std::string startSubstring = "% frame";
	const std::string endString = "% end";

	// define vector for storing frames which store lines corresponding to the frames
	// will eventually remove vector of frames  discard frame data after doing mafs
	std::vector <std::vector <std::string> >  vectorOfFrames;

	std::vector <Frame> vectorOfFrameObjects ;

	get_file_contents(fileName, startSubstring, endString, vectorOfFrames,
					  vectorOfFrameObjects);

	return 0;
}
