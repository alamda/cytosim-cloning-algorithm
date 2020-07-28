#include "calculate.h"
#include "frame.h"
#include "parse.h"
#include "simul.h"

#include <cstdio>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

/**	@brief 	Takes info from data file and populates Frame object.

	@param 	line 		-	std::string
	@param 	frame 		-	reference to Frame object
	*/
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
			std::string matchStr = match.str() ;
			frame.dataCategories.push_back(matchStr);
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
			std::string matchStr = match.str();
			dataEntries.push_back(matchStr) ;
		}

		frame.dataLines.push_back(dataEntries) ;

	}
}

/** @brief 	Check if simulation output data is 2D or 3D, returns true if 3D

	@param 	frame 		- 	reference to Frame object
	@return threeDimData -	bool

	@todo 	Works with 3D output file, need to check that it returns false for a 2D output file.
	*/
bool check_dimension(Frame & frame)
{
	std::regex rgx("pos[12]Z"); // check if Z coordinate is present
	std::smatch match ;

	bool threeDimData ;

	std::vector <std::string>::iterator dataPtr = frame.dataCategories.begin(),
										endPtr = frame.dataCategories.end() ;

	do
	{
			threeDimData = std::regex_search(*dataPtr, match, rgx) ;
			++dataPtr ;

	} while (!threeDimData && dataPtr != endPtr) ;

	return threeDimData ;
}
/**	@brief 	Takes info from Frame object, then creates and populates Linker objects

	@param 	frame 		- 	reference to Frame object

	*/
// Takes info from Frame object and populates Linker objects
void process_frame(Frame & frame)
{
	bool threeDimData = check_dimension(frame) ;

	for (auto line : frame.dataLines)
	{
		if (line.size() > 0)
		{
			Linker linker ;

			linker.classOfObject = std::stoi(line.at(0)) ;
			linker.linkerIdentity = std::stoi(line.at(1)) ;

			linker.headOne.fiberIdentity = std::stoi(line.at(2)) ;
			linker.headOne.abscissa  = std::stof(line.at(3)) ;

			if (threeDimData)
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
				linker.cosAngle = std::stof( line.at(13) ) ;
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
				linker.cosAngle = std::stof( line.at(11) ) ;
			}

			frame.linkerObjects.push_back(linker) ;

			frame.numLinkers = frame.linkerObjects.size() ;


		}
		else
			frame.numLinkers = 0 ;


	}

}

/**	@brief 	Extract and process data from output file previously created by Cytosim

	@param 	fileName 		- 	std::string
	@param	simul			-	reference to Simul object

	Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
	*/
//
void get_output_file_contents( std::string fileName, Simul & simul )
{
	// open file
	std::ifstream dataFile(fileName.c_str());

	while (dataFile)
	{
		// Define string variable
		std::string line ;
		int frameIdx = 0;

		// static const Frame emptyFrame;
		Frame currentFrame;
		Frame previousFrame ;

		// Read line by line and sort into frames
		// line is a c string
		while (std::getline(dataFile, line))
		{
			std::size_t foundEnd ;

			foundEnd = line.find(currentFrame.endStr);

			// If the line does not match endString
			// fun fact: if (foundEnd == std::string::npos) does produce desired results
			// which is why the "double negative"/(!(!=)) is necessary
			if (!(foundEnd != std::string::npos))
			{
				process_line(line, currentFrame);
			}
			else // If line DOES match endString
			{
				process_frame(currentFrame) ;

				frameIdx++ ;

				calculate_frame(currentFrame, previousFrame, simul) ;

				// Move current frame object to previousFrame
				previousFrame = currentFrame ;

				// Create new frame object
				currentFrame = Frame() ;
			}
		}
	printf("Total number of frames: %d\n", frameIdx);
	}
	//Close The File
	dataFile.close();
}

/**	@brief 	Obtain simulation parameters from *.cym Cytosim config file

	@param	simul		-	reference to Simul object
	@param 	fileName	-	std::string

	*/
void get_simulation_params(Simul & simul, std::string fileName)
{
	//simul.unloadedSpeed
	std::regex rgxUnload("unloaded_speed");
	//simul.stallForce ;
	std::regex rgxStall("stall_force");

	std::regex rgxFloat("-?\\d+\\.?\\d*") ;

	// open file
	std::ifstream configFile(fileName.c_str());

	while (configFile)
	{
		std::string line ;

		while (std::getline(configFile, line))
		{
			std::smatch matchLine ;
			std::smatch matchFloat ;

			if ( std::regex_search(line, matchLine, rgxUnload) )
			{
				if ( std::regex_search(line, matchFloat, rgxFloat))
					simul.unloadedSpeed = std::stof(matchFloat.str(0));
			}
			else if ( std::regex_search(line, matchLine, rgxStall))
			{
				if (std::regex_search(line, matchFloat, rgxFloat))
					simul.stallForce = std::stof(matchFloat.str(0));
			}
		}

		printf( "unloaded_speed: %f\n",simul.unloadedSpeed ) ;
		printf( "stall_force: %f\n", simul.stallForce ) ;

		printf("\n") ;
	}
	configFile.close() ;
}
