#include "frame.h"
#include "linker.h"
#include "head.h"
#include <cstdio>
#include <regex>
#include <vector>
#include <string>

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

		std::vector <std::string> dataEntries ;

		for (std::sregex_iterator i = dataBegin; i != dataEnd; ++i)
		{
			match = *i ;
			std::string match_str = match.str();
			dataEntries.push_back(match_str) ;
		}

		frame.dataLines.push_back(dataEntries) ;

	}
}

// Check if simulation is 3D, returns true if 3D
// Works with 3D output file, need to check that it returns false for 2D output file
bool check_dimension(Frame & frame)
{
	std::regex rgx("pos[12]Z"); // check if Z coordinate is present
	std::smatch match ;

	bool threeD_data ;

	std::vector <std::string>::iterator data_ptr = frame.dataCategories.begin(),
										end_ptr = frame.dataCategories.end() ;

	do
	{
			threeD_data = std::regex_search(*data_ptr, match, rgx) ;
			++data_ptr ;

	} while (!threeD_data && data_ptr != end_ptr) ;

	return threeD_data ;
}

// Takes info from Frame object and populates Linker objects
void process_frame(Frame & frame)
{
	bool threeD_data = check_dimension(frame) ;

	for (auto line : frame.dataLines)
	{
		if (line.size() > 0)
		{
			Linker linker ;

			linker.classOfObject = std::stoi(line.at(0)) ;
			linker.linkerIdentity = std::stoi(line.at(1)) ;

			linker.headOne.fiberIdentity = std::stoi(line.at(2)) ;
			linker.headOne.abscissa  = std::stof(line.at(3)) ;

			if (threeD_data)
			{
				linker.headOne.positionVector.push_back( std::stof( line.at(4) ) ) ;
				linker.headOne.positionVector.push_back( std::stof( line.at(5) ) ) ;
				linker.headOne.positionVector.push_back( std::stof( line.at(6) ) ) ;

				linker.headTwo.fiberIdentity = std::stoi(line.at(7)) ;
				linker.headTwo.abscissa  = std::stof(line.at(8)) ;

				linker.headTwo.positionVector.push_back( std::stof( line.at(9) ) ) ;
				linker.headTwo.positionVector.push_back( std::stof( line.at(10) ) ) ;
				linker.headTwo.positionVector.push_back( std::stof( line.at(11) ) ) ;

				linker.force = std::stof( line.at(12) ) ;
				linker.cos_angle = std::stof( line.at(13) ) ;
			}
			else
			{
				linker.headOne.positionVector.push_back( std::stof( line.at(4) ) ) ;
				linker.headOne.positionVector.push_back( std::stof( line.at(5) ) ) ;

				linker.headTwo.fiberIdentity = std::stoi(line.at(6)) ;
				linker.headTwo.abscissa  = std::stof(line.at(7)) ;

				linker.headTwo.positionVector.push_back( std::stof( line.at(8) ) ) ;
				linker.headTwo.positionVector.push_back( std::stof( line.at(9) ) ) ;

				linker.force = std::stof( line.at(10) ) ;
				linker.cos_angle = std::stof( line.at(11) ) ;
			}

			frame.linkerObjects.push_back(linker) ;
		}
	}
}

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
void get_output_file_contents( std::string fileName, Simulation & simul )
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

				frame_idx++ ;

				if (frame_idx > 1)
				{
					// do calculations on frame and previousFrame
					calculate_velocity(simul) ;

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
