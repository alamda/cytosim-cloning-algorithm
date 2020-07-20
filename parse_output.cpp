#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory> // For unique_ptr
#include "parse_output.h"

struct Frame
{
	int frameNumber ;
	const std::string frameStr = "frame";

	double timeStamp ;
	const std::string timeStr = "time";

	std::string reportCommand ;
	const std::string reportStr = "report";

	std::string dataCategories ;
	const std::string categoriesStr = "class";

	std::vector <std::string> dataLines ;
};

void process_frame(std::vector <std::string> & vectorOfFrameContent, std::vector <Frame> & vectorOfFrameObjects)
{
	Frame frame ;

	for(std::string & line : vectorOfFrameContent)
	{


		if (line.find(frame.frameStr) != std::string::npos)
		{
			printf("%c", line.c_str());// Extract frame number int
		}
		// else if (/* condition */)
		// {
		// 	// Extract timestamp double
		// }
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
			// Line contains string of length > 0 then save it in vector
			if(line.size() > 0)
			{
				// check if the line contains the string denoting the start of the frame
				std::size_t found = line.find(startSubstring);

				// if start substring is found in the line
				if (found != std::string::npos)
				{
					// empty out the vector of frame content
					vectorOfFrameContent.clear() ;

					printf("start of frame %d\n", frameNumber);
				}

				vectorOfFrameContent.push_back(line);

				// check if the line contains the string denoting the end of the frame
				found = line.find(endString);

				if (found != std::string::npos)
				{
					vectorOfFrames.push_back(vectorOfFrameContent);

					printf("end of frame %d, number of lines for this frame is %d\n\n", frameNumber, vectorOfFrameContent.size());

					frameNumber++ ;

					process_frame(vectorOfFrameContent, vectorOfFrameObjects);

					if (frameNumber > 1)
					{
						// do calculations on two adjacent frames
					}

				}
			}


		}

	printf("Total number of frames: %d", frameNumber);

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

	// define vector for storing lines extracted from file
	// std::vector <std::string> vectorOfFileLines;

	// define vector for storing frames which store lines corresponding to the frames
	std::vector <std::vector <std::string> >  vectorOfFrames;

	std::vector <Frame> vectorOfFrameObjects ;

	//For reading large files:
	// Source: https://stackoverflow.com/questions/34751873/how-to-read-huge-file-in-c

	get_file_contents(fileName, startSubstring, endString, vectorOfFrames,
					  vectorOfFrameObjects);

	return 0;
}
