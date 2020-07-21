#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <iterator> // for sregex_iterator
#include "parse_output.h"

typedef struct Linker
{
	int classOfObject, linkerIdentity, fiberOneIdentity, fiberTwoIdentity ;
	float abscissaOne , abscissaTwo ;
	float posOneX, posOneY, posOneZ;
	float posTwoX, posTwoY, posTwoZ;
	float force, cos_angle ;

} Linker_t ;

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

	std::vector <Linker> linkerObjects ;

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
	else if (line.find(frame.categoriesStr) != std::string::npos)
	{
		// Extract string with category names of data in file
		// not going to do anything for now

		// maybe eventually will have some code which auto-detects categories
		// and creates a linker class with appropriate variables
	}
	else
	{
		// Extract vector of strings of data lines for the frame
		std::regex rgx("[0-9]+.[0-9]*");

		// https://en.cppreference.com/w/cpp/regex/regex_iterator
		auto dataBegin = std::sregex_iterator(line.begin(), line.end(),  rgx);
		auto dataEnd = std::sregex_iterator();

		// need to work on the code below - store retrieved values in Linker object

		for (std::sregex_iterator i = dataBegin; i != dataEnd; ++i)
		{
			match = *i ;
			std::string match_str = match.str();
			std::cout << match_str << " " ;
		}

		std::cout << std::endl;
	}
}

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
 void get_file_contents( std::string fileName,
						std::string const endString,
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

				frame_idx++ ;

				if (frame_idx > 1)
				{
					// do calculations on frame and previousFrame
				}

				// Move current frame object to previousFrame
				previousFrame = frame ;
				// Create new frame object
				frame = Frame() ;

				// new line to separate frames
				std::cout << std::endl;
				std::cout << std::endl;
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

	std::vector <Frame> vectorOfFrameObjects ;

	get_file_contents(fileName, endString, vectorOfFrameObjects);

	return 0;
}
