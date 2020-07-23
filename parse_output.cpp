#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <iterator> // for sregex_iterator
#include "parse_output.h"

typedef struct Simulation
{
	float unloaded_speed, stall_force ;
} Simulation_t ;

typedef struct Head
{
	int fiberIdentity ;
	float abscissa ;
	std::vector <float> positionVector  ;

	std::vector <float> velocityVector, movementDirVector ;
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

	std::vector <std::vector <std::string> > dataLines;

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
				linker.headOne.positionVector.push_back( stof( line.at(4) ) ) ;
				linker.headOne.positionVector.push_back( stof( line.at(5) ) ) ;
				linker.headOne.positionVector.push_back( stof( line.at(6) ) ) ;

				linker.headTwo.fiberIdentity = std::stoi(line.at(7)) ;
				linker.headTwo.abscissa  = std::stof(line.at(8)) ;

				linker.headTwo.positionVector.push_back( stof( line.at(9) ) ) ;
				linker.headTwo.positionVector.push_back( stof( line.at(10) ) ) ;
				linker.headTwo.positionVector.push_back( stof( line.at(11) ) ) ;

				linker.force = stof( line.at(12) ) ;
				linker.cos_angle = stof( line.at(13) ) ;
			}
			else
			{
				linker.headOne.positionVector.push_back( stof( line.at(4) ) ) ;
				linker.headOne.positionVector.push_back( stof( line.at(5) ) ) ;

				linker.headTwo.fiberIdentity = std::stoi(line.at(6)) ;
				linker.headTwo.abscissa  = std::stof(line.at(7)) ;

				linker.headTwo.positionVector.push_back( stof( line.at(8) ) ) ;
				linker.headTwo.positionVector.push_back( stof( line.at(9) ) ) ;

				linker.force = stof( line.at(10) ) ;
				linker.cos_angle = stof( line.at(11) ) ;
			}

			frame.linkerObjects.push_back(linker) ;
		}
	}
}

void calculate_velocity()
{

}

void calculate_w_dot(Frame currentFrame, Frame previousFrame)
{
	// for (linker : currentFrame)
	//		if linker.linkerIdentity also appears in previousFrame
	//			do calculations
	//			store in vector ??
}

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
void get_output_file_contents( std::string fileName )
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

// obtain simulation parameters from config.cym file
void get_simulation_params(Simulation & simul, std::string fileName)
{
	//simul.unloaded_speed
	std::regex rgx_unload("unloaded_speed");
	//simul.stall_force ;
	std::regex rgx_stall("stall_force");

	std::regex rgx_float("-?\\d+\\.?\\d*") ;

	// open file
	std::ifstream configFile(fileName.c_str());

	while (configFile)
	{
		std::string line ;

		while (std::getline(configFile, line))
		{
			std::smatch match_line ;
			std::smatch match_float ;

			if ( std::regex_search(line, match_line, rgx_unload) )
			{
				if ( std::regex_search(line, match_float, rgx_float))
					simul.unloaded_speed = std::stof(match_float.str(0));
			}
			else if ( std::regex_search(line, match_line, rgx_stall))
			{
				if (std::regex_search(line, match_float, rgx_float))
					simul.stall_force = std::stof(match_float.str(0));
			}
		}

		std::cout << "unloaded_speed: " << simul.unloaded_speed << std::endl ;
		std::cout << "stall_force: " << simul.stall_force << std::endl ;
	}
	configFile.close() ;
}

int main()
{
	Simulation simul ;

	const std::string paramFileName = "config.cym";

	get_simulation_params(simul, paramFileName) ;

	// Name of data file to be read:
	const std::string dataFileName = "link.txt";

	get_output_file_contents(dataFileName);

	return 0;
}
