#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include "parse_output.h"

typedef struct Frame
{
	int frameNumber ;
	static std::string frameStr ;

	float timeStamp ;
	static std::string timeStr ;

	std::string reportCommand ;
	static std::string reportStr ;

	std::string dataCategories ;
	static std::string categoriesStr ;

	std::vector <std::string> dataLines ;

} Frame_t ;

std::string Frame::frameStr = "frame";
std::string Frame::timeStr = "time";
std::string Frame::reportStr = "report";
std::string Frame::categoriesStr = "class";

void process_line(std::string line, Frame & frame)
{
	std::smatch match ;

	if (line.find(frame.frameStr) != std::string::npos)
	{	// Extract int with frame number
		std::regex rgx("[0-9]+");

		if (std::regex_search(line, match, rgx))
			frame.frameNumber =  std::stoi(match.str(0));

	}
	else if (line.find(frame.timeStr) != std::string::npos)
	{	// Extract float with time stamp
		std::regex rgx("[0-9]+.[0-9]+");

		if (std::regex_search(line, match, rgx))
			frame.timeStamp =  std::stof(match.str(0));

	}
	else if (line.find(frame.reportStr) != std::string::npos)
	{	// Extract string with report command used to generate data file
		std::regex rgx("[a-z]+:[a-z]+");

		if (std::regex_search(line, match, rgx))
			frame.reportCommand = match.str(0);

	}
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
						std::string const endString,
						std::vector <std::vector <std::string> > & vectorOfFrames,
						std::vector <Frame> & vectorOfFrameObjects )
{
	// open file
	std::ifstream dataFile(fileName.c_str());

	while (dataFile)
	{
		// Define string variable
		std::string line ;
		int frame_idx = 0;

		// static const Frame emptyFrame;
		Frame frame;
		Frame previousFrame ;

		// Read line by line and sort into frames
		// line ins a c string
		while (std::getline(dataFile, line))
		{
			std::size_t found_end ;

			found_end = line.find(endString);

			// If the line does not match endString
			if (!(found_end != std::string::npos))
			{
				process_line(line, frame);
			}
			else // If line matches endString
			{

				// will remove vector of frames
				vectorOfFrameObjects.push_back(frame);

				// printf("end of frame %d, pushing back frame objects to vector\n", frame_idx);

				frame_idx++ ;

				if (frame_idx > 1)
				{
					// std::cout << frame.frameNumber << " "<< previousFrame.frameNumber << std::endl;
				}

				// Create new frame object
				previousFrame = frame ;
				frame = Frame() ;
			}
		}
	printf("Total number of frames: %d\n", frame_idx);
	}

	//Close The File
	dataFile.close();
}

int main()
{
	// Name of data file to be read:
	const std::string fileName = "link.txt";
	const std::string endString = "end";

	// define vector for storing frames which store lines corresponding to the frames
	// will eventually remove vector of frames  discard frame data after doing mafs
	std::vector <std::vector <std::string> >  vectorOfFrames;

	std::vector <Frame> vectorOfFrameObjects ;

	get_file_contents(fileName, endString, vectorOfFrames, vectorOfFrameObjects);

	return 0;
}
