#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <iterator> // for sregex_iterator
#include "parse_output.h"

typedef struct Head
{
	int fiberIdentity ;
	float abscissa ;
	float position ;
} Head_t ;

typedef struct Linker
{
	int classOfObject, linkerIdentity ;
	float force, cos_angle ;

	Head headOne ;
	Head headTwo ;

	std::vector <Head> headObjects ;
} Linker_t ;

typedef struct Frame
{
	int frameNumber ;
	static std::string frameStr ;

	float timeStamp ;
	static std::string timeStr ;

	std::string reportCommand ;
	static std::string reportStr ;

	std::vector <std::string> dataCategories ;
	static std::string categoriesStr ;

	std::vector <std::string> dataEntries;

	static std::string endStr ;

	std::vector <Linker> linkerObjects ;

	// Values that will need to be calculated
	float rateOfWork, velocity ;
} Frame_t ;

std::string Frame::frameStr = "frame";
std::string Frame::timeStr = "time";
std::string Frame::reportStr = "report";
std::string Frame::categoriesStr = "class";
std::string Frame::endStr = "end";

// Takes info from data file and populates Frame object
void process_line(std::string line, Frame & frame)
{
	std::smatch match ;

	if (line.find(frame.frameStr) != std::string::npos)
	{	// Extract int with frame number
		std::regex rgx("\\d+");

		if (std::regex_search(line, match, rgx))
			frame.frameNumber =  std::stoi(match.str(0));

	}
	else if (line.find(frame.timeStr) != std::string::npos)
	{	// Extract float with time stamp
		std::regex rgx("\\d+.\\d+");

		if (std::regex_search(line, match, rgx))
			frame.timeStamp =  std::stof(match.str(0));

	}
	else if (line.find(frame.reportStr) != std::string::npos)
	{	// Extract string with report command used to generate data file
		std::regex rgx("\\w+:\\w+");

		if (std::regex_search(line, match, rgx))
			frame.reportCommand = match.str(0);

	}
	else if (line.find(frame.categoriesStr) != std::string::npos)
	{
		// Extract string with category names of data in file
		std::regex rgx("\\w+") ;

		auto categoriesBegin = std::sregex_iterator(line.begin(), line.end(), rgx);
		auto categoriesEnd = std::sregex_iterator() ;

		for (std::sregex_iterator i = categoriesBegin; i != categoriesEnd; ++i)
		{
			match = *i ;
			std::string match_str = match.str() ;
			frame.dataCategories.push_back(match_str);
		}

		// maybe eventually will have some code which auto-detects categories
		// and creates a linker class with appropriate variables
	}
	else
	{
		// Extract vector of strings of data lines for the frame
		std::regex rgx("-?\\d+\\.?\\d*");

		// https://en.cppreference.com/w/cpp/regex/regex_iterator
		auto dataBegin = std::sregex_iterator(line.begin(), line.end(),  rgx);
		auto dataEnd = std::sregex_iterator();

		for (std::sregex_iterator i = dataBegin; i != dataEnd; ++i)
		{
			match = *i ;
			std::string match_str = match.str();
			frame.dataEntries.push_back(match_str) ;
		}

	}
}

// Takes info from Frame object and populates Linker objects
void process_frame(Frame & frame)
{
	//
}

// Takes info from Linker object and populates Hand objects
void process_linker(Linker & linker)
{
	//
}

void calculate_w_dot(Frame currentFrame, Frame previousFrame)
{
	// for (linker : currentFrame)
	//		if linker.linkerIdentity also appears in previousFrame
	//			do calculations
	//			store in vector ??
}

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
 void get_file_contents( std::string fileName )
{
	// open file
	std::ifstream dataFile(fileName.c_str());

	while (dataFile)
	{
		// Define string variable
		std::string line ;
		int frame_idx = 0;

		// static const Frame emptyFrame;
		Frame currentFrame;
		Frame previousFrame ;

		// Read line by line and sort into frames
		// line is a c string
		while (std::getline(dataFile, line))
		{
			std::size_t found_end ;

			found_end = line.find(currentFrame.endStr);

			// If the line does not match endString
			// fun fact: if (found_end == std::string::npos) does produce desired results
			// which is why the "double negative"/(!(!=)) is necessary
			if (!(found_end != std::string::npos))
			{
				process_line(line, currentFrame);
			}
			else // If line DOES match endString
			{
				process_frame(currentFrame) ;
				// process_linker() ;

				frame_idx++ ;

				if (frame_idx > 1)
				{
					// do calculations on frame and previousFrame
					// calculate linker.velocity and linker.rateOfWork

					// calculations will be done by function calculate_w_dot()

					calculate_w_dot(currentFrame, previousFrame);
				}

				// Move current frame object to previousFrame
				previousFrame = currentFrame ;

				// Create new frame object
				currentFrame = Frame() ;
			}
		}
	printf("\nTotal number of frames: %d\n", frame_idx);
	}
	//Close The File
	dataFile.close();
}

int main()
{
	// Name of data file to be read:
	const std::string fileName = "link.txt";

	get_file_contents(fileName);

	return 0;
}
