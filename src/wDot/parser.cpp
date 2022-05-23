#include "calculator.h"
#include "frame.h"
#include "linker.h"
#include "hand.h"
#include "parser.h"
#include "simul.h"

#include <cstdio>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include <iostream>

/**	@brief 	Takes info from data file and populates Frame object.

	@param 	line 		-	std::string
	@param 	frame 		-	reference to Frame object
	*/
void process_line(std::string & line, Frame & frame)
{
	std::smatch match ;

	if (line.find(frame.frameStr) != std::string::npos)
	{	// Extract int with frame number
		std::regex rgx("[0-9]+");

		if (std::regex_search(line, match, rgx))
		{
			frame.frameNumber =  std::stoi(match.str(0));
			// printf("frame.frameNumber: %d\n", frame.frameNumber) ;
		}

	}
	else if (line.find(frame.timeStr) != std::string::npos)
	{	// Extract float with time stamp
		// This value will be overwritten during calculations to have a higher precision.
		// Keeping this code because something seems to break when I remove it
		// and other exciting bugs await me so I'll go with the lazy solution
		// (which is to let this code be) for now.
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

		// https://en.cppreference.com/w/cpp/regex/regex_iterator
		auto categoriesBegin = std::sregex_iterator(line.begin(), line.end(), rgx);
		auto categoriesEnd = std::sregex_iterator() ;

		// Iterate over each word in the string
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
		// Extract vector of strings of data entries for the frame
		std::regex rgx("-?\\d+\\.?\\d*");

		// https://en.cppreference.com/w/cpp/regex/regex_iterator
		auto dataBegin = std::sregex_iterator(line.begin(), line.end(),  rgx);
		auto dataEnd = std::sregex_iterator();

		// Empty string vector for storing data entries for a line
		std::vector <std::string> dataEntries ;

		// Iterate over each data entry in the string
		for (std::sregex_iterator i = dataBegin; i != dataEnd; ++i)
		{
			match = *i ;
			std::string matchStr = match.str();
			dataEntries.push_back(matchStr) ;
		}

		// Add vector with data entries from line to frame's vector of vector of strings
		// Each vector of strings corresponds to data belonging to one
		// doubly-bound cross-linker.
		frame.dataLines.push_back(dataEntries) ;

	}
}

/**	@brief 	Takes info from Frame object, then creates and populates Linker objects

	@param 	frame 		- 	reference to Frame object

	*/
void process_frame(Simul & simul, Frame & frame)
{
	// bool threeDimData = check_dimension(frame) ;

	for (auto line : frame.dataLines)
	{
		if (line.size() > 0)
		{
			Linker linker ;

			linker.classOfObject = std::stoi(line.at(0)) ;
			linker.linkerIdentity = std::stoi(line.at(1)) ;

			linker.handOne.fiberIdentity = std::stoi(line.at(2)) ;
			linker.handOne.abscissa  = std::stof(line.at(3)) ;

			if (simul.dimension == 3)
			{
				linker.handOne.positionVector_std.push_back( std::stof( line.at(4) ) ) ;
				linker.handOne.positionVector_std.push_back( std::stof( line.at(5) ) ) ;
				linker.handOne.positionVector_std.push_back( std::stof( line.at(6) ) ) ;

				linker.handOne.positionVector_eigen  = convert_std_vec_to_eigen_vec(linker.handOne.positionVector_std) ;

				linker.handOne.directionVector_std.push_back( std::stof( line.at(7) ) ) ;
				linker.handOne.directionVector_std.push_back( std::stof( line.at(8) ) ) ;
				linker.handOne.directionVector_std.push_back( std::stof( line.at(9) ) ) ;

				linker.handOne.directionVector_eigen = convert_std_vec_to_eigen_vec(linker.handOne.directionVector_std).normalized() ;

				linker.handTwo.fiberIdentity = std::stoi(line.at(10)) ;
				linker.handTwo.abscissa  = std::stof(line.at(11)) ;

				linker.handTwo.positionVector_std.push_back( std::stof( line.at(12) ) ) ;
				linker.handTwo.positionVector_std.push_back( std::stof( line.at(13) ) ) ;
				linker.handTwo.positionVector_std.push_back( std::stof( line.at(14) ) ) ;

				linker.handTwo.positionVector_eigen = convert_std_vec_to_eigen_vec(linker.handTwo.positionVector_std) ;

				linker.handTwo.directionVector_std.push_back( std::stof( line.at(15) ) ) ;
				linker.handTwo.directionVector_std.push_back( std::stof( line.at(16) ) ) ;
				linker.handTwo.directionVector_std.push_back( std::stof( line.at(17) ) ) ;

				linker.handTwo.directionVector_eigen = convert_std_vec_to_eigen_vec(linker.handTwo.directionVector_std).normalized() ;

				linker.force = std::stof( line.at(18) ) ;
				linker.cosAngle = std::stof( line.at(19) ) ;
			}
			else
			{
				linker.handOne.positionVector_std.push_back( std::stof( line.at(4) ) ) ;
				linker.handOne.positionVector_std.push_back( std::stof( line.at(5) ) ) ;

				linker.handOne.positionVector_eigen = convert_std_vec_to_eigen_vec(linker.handOne.positionVector_std) ;

				linker.handOne.directionVector_std.push_back( std::stof( line.at(6) ) ) ;
				linker.handOne.directionVector_std.push_back( std::stof( line.at(7) ) ) ;

				linker.handOne.directionVector_eigen = convert_std_vec_to_eigen_vec(linker.handOne.directionVector_std).normalized() ;

				linker.handTwo.fiberIdentity = std::stoi(line.at(8)) ;
				linker.handTwo.abscissa  = std::stof(line.at(9)) ;

				linker.handTwo.positionVector_std.push_back( std::stof( line.at(10) ) ) ;
				linker.handTwo.positionVector_std.push_back( std::stof( line.at(11) ) ) ;

				linker.handTwo.positionVector_eigen = convert_std_vec_to_eigen_vec(linker.handTwo.positionVector_std) ;

				linker.handTwo.directionVector_std.push_back( std::stof( line.at(12) ) ) ;
				linker.handTwo.directionVector_std.push_back( std::stof( line.at(13) ) ) ;

				linker.handTwo.directionVector_eigen = convert_std_vec_to_eigen_vec(linker.handTwo.directionVector_std).normalized() ;

				linker.force = std::stof( line.at(14) ) ;
				linker.cosAngle = std::stof( line.at(15) ) ;
			}

			frame.linkerObjects.push_back(linker) ;

			frame.numLinkers = frame.linkerObjects.size() ;
		}
		else
			frame.numLinkers = 0 ;
	}
}

/**	@brief 	Extract and process data from output file previously created by Cytosim

	@param	simul					-	reference to Simul object
	@param 	dataFileName 			- 	std::string
	@param	observableDataFileName			-	std::string
	@param	observableIntegralFileName	- std::string

	Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/

	*/
void process_data_file( Simul & simul, std::string dataFileName, std::string observableDataFileName, std::string observableIntegralFileName  )
{
	// Open file with Cytosim data for reading
	std::ifstream dataFile(dataFileName.c_str());

	// Open file for writing observable data for each frame in trajectory
	std::ofstream observableDataFile(observableDataFileName.c_str()) ;

	// Open file for writing observableIntegral value for the trajectory
	std::ofstream observableIntegralFile(observableIntegralFileName.c_str()) ;

	// If input dataFile was opened successfully
	while (dataFile)
	{
		// Define string variable
		std::string line ;

		// Frame counting variable - currently unused, but keeping for debugging
		int frameIdx = 0;

		// Declare frame objects
		Frame currentFrame;
		Frame previousFrame ;

		// set the observable value for fresh frame to zero
		currentFrame.observable = 0.0 ;

		// Set dt value for frames to zero so that calculation for
		// the zeroth frame can occur
		// currentFrame.dt = 0.0 ;
		previousFrame.dt = 0.0 ;

		// Set trajectory value to zero, will be adding to it later
		simul.observableIntegral = 0.0 ;

		// Read line by line and sort into frames, line is a c string
		while (std::getline(dataFile, line))
		{
			std::size_t foundEnd ;

			// Check if current line contains the word "end"
			foundEnd = line.find(currentFrame.endStr);

			// If the line does not match endString
			// fun fact: {if (foundEnd == std::string::npos)} does not produce
			// desired results, which is why the "double negative"/(!(!=)) is necessary
			if (!(foundEnd != std::string::npos))
			{
				// Identify which information the line contains and place into
				// data member of the Frame object for current frame
				process_line(line, currentFrame);
			}
			else // If line DOES match endString
			{
				// Calculate the time stamp for the frame
				// Using a calculated version instead of directly extracting from
				// the output file because the output file floating point values
				// have limited precision (4 decimal points).  This becomes an
				// issue for smaller time step sizes.
				currentFrame.timeStamp = currentFrame.frameNumber * simul.timeStepSize * (simul.numSteps / simul.numFrames);

				// printf("simul.timeStepSize: %f\n", simul.timeStepSize) ; // works fine
				// printf("currentFrame.frameNumber: %i\n", currentFrame.frameNumber) ; // works fine
				// printf("simul.numSteps: %i\n", simul.numSteps) ; // did not work, works now
				// printf("simul.numFrames: %i\n", simul.numFrames) ;
				// printf("currentFrame.timeStamp: %f\n", currentFrame.timeStamp) ; // works

				currentFrame.dt = currentFrame.timeStamp - previousFrame.timeStamp ;

				// Sort data identified by process_line()
				// into members of the Frame object and convert to appropriate types
				process_frame(simul, currentFrame) ;

				// printf("frame.frameNumber %d\tframe.numLinkers %d\tframe.timeStamp %f\n", currentFrame.frameNumber, currentFrame.numLinkers, currentFrame.timeStamp) ;

				// Perform calculations on data
				// - calculate observable for frame
				// - update simul.observableIntegral
				calculate_frame(simul, currentFrame) ;

				// Write observable values for each frame to file
				observableDataFile << currentFrame.timeStamp ;
				observableDataFile << "\t" ;
				observableDataFile << currentFrame.observable ;
				observableDataFile << "\n" ;

				// Store currentFrame object in the previousFrame object
				previousFrame = currentFrame ;

				// Create new frame object
				currentFrame = Frame() ;

				// Increase frame counter (for debugging)
				frameIdx++ ;
			}
		}
	// printf("Total number of frames: %d\n", frameIdx);
	// printf("w dot integral for trajectory: %f\n", simul.observableIntegral) ;

	// Once all frames are processed, write integral value to file
	observableIntegralFile << simul.observableIntegral ;

	printf("\nsimul.observableIntegral:\t\t\t%f\tpN.um\n", simul.observableIntegral) ;
	}

	//Close the files
	dataFile.close();
	observableDataFile.close()  ;
	observableIntegralFile.close() ;
}

/**	@brief 	Obtain simulation parameters from *.cym Cytosim config file

	These simulation parameters are needed to do calculations

	@param	simul		-	reference to Simul object
	@param 	fileName	-	std::string

	*/
void get_simulation_params(Simul & simul, std::string configFileName)
{
	// Only done once per trajectory

	//simul.timeStepSize ;
	std::regex rgxTimeStep("time_step") ;
	//simul.dimension ;
	std::regex rgxDimension("dim") ;
	//simul.numFrames ;
	std::regex rgxNumFrames("nb_frames") ;
	//simul.numSteps ;
	std::regex rgxNumSteps("run \\d+") ;
	std::regex rgxNumSteps2("nb_steps") ;
	std::regex rgxDuration("duration") ;

	//simul.unloadedSpeed
	std::regex rgxUnload("unloaded_speed");
	//simul.stallForce ;
	std::regex rgxStall("stall_force");

	// Regex for all kinds of numbers: positive and negative ints and floats
	std::regex rgxNum("-?\\d+\\.?\\d*") ;

	// Open Cytosim configuration file
	std::ifstream configFile(configFileName.c_str());

	// If configuration file was opened successfully
	while (configFile)
	{
		// Declare empty string variable in which file line contents will be
		// temporarily stored
		std::string line ;

		// Read config file line-by-line
		// Since each line is checked for all regex patterns, the most recent
		// (latest) value of a parameter is what gets recorded
		// For instance, if the time step is set at the beginning and then
		// changed later, the second value will be stored as the time step length
		while (std::getline(configFile, line))
		{
			// "Container-like class used to store the matches found on the
			// target sequence of characters after a regex matching operation,
			// each match being of the corresponding sub_match type."
			// See http://www.cplusplus.com/reference/regex/match_results/
			std::smatch matchLine ;
			std::smatch matchNum ;

			if (std::regex_search(line, matchLine, rgxTimeStep))
			{	// If line contains time step string
				if (std::regex_search(line, matchNum, rgxNum))
					simul.timeStepSize = std::stof(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxDimension))
			{	// If line contains dimension string
				if (std::regex_search(line, matchNum, rgxNum))
					simul.dimension = std::stoi(matchNum.str(0)) ;
			}
			else if (std::regex_search(line, matchLine, rgxNumFrames))
			{	// If line contains number of frames string
				if (std::regex_search(line, matchNum, rgxNum))
				{
					simul.numFrames = std::stoll(matchNum.str(0));

					// printf("simul.numFrames:\t\t\t%d\n", simul.numFrames) ;
				}
			}
			else if (std::regex_search(line, matchLine, rgxNumSteps) ||
					 std::regex_search(line, matchLine, rgxNumSteps2))
			{	// If line contains "run [### system_name]" command or nb_steps
				if (std::regex_search(line, matchNum, rgxNum))
				{
					simul.numSteps = std::stoi(matchNum.str(0));

					// printf("simul.numSteps:\t\t\t\t%d\n", simul.numSteps) ;
				}
			}
			else if (std::regex_search(line, matchLine, rgxDuration))
			{	// If line contains duration parameter
				if (std::regex_search(line, matchNum, rgxNum))
				{
					simul.duration = std::stof(matchNum.str(0)) ;

					simul.numSteps = simul.duration/simul.timeStepSize +1 ;

					// printf("simul.numSteps:\t\t\t\t%d\n", simul.numSteps) ;
				}
			}
			else if ( std::regex_search(line, matchLine, rgxUnload) )
			{	// If line contains unloaded speed string
				if ( std::regex_search(line, matchNum, rgxNum))
					simul.unloadedSpeed = std::stof(matchNum.str(0));
			}
			else if ( std::regex_search(line, matchLine, rgxStall))
			{	// If line contains stall force string
				if (std::regex_search(line, matchNum, rgxNum))
					simul.stallForce = std::stof(matchNum.str(0));
			}
		}
		// printf( "simul.unloadedSpeed:\t\t\t%f\tum/s\n",simul.unloadedSpeed ) ;
		// printf( "simul.stallForce:\t\t\t%f\tpN\n", simul.stallForce ) ;
	}

	configFile.close() ;
}

void get_object_props(Simul & simul, std::string propFileName)
{

	std::regex rgxSetHand(R"(set hand.*\n\{((.|\n)*?)\})") ;
	std::regex rgxHandName("set hand") ;

	std::regex rgxSetCouple(R"(set couple.*\n\{((.|\n)*?)\})");
	std::regex rgxCoupleName("set couple") ;

	//simul.unloadedSpeed
	std::regex rgxUnload("unloaded_speed");
	//simul.stallForce ;
	std::regex rgxStall("stall_force");

	std::regex rgxNum("-?\\d+\\.?\\d*") ;

	// Open the file with object properties
	std::ifstream propFile(propFileName.c_str()) ;

	// Load contents of file into string variable
	// Important: file must be relatively small!
	// Make sure to generate property.txt with
	// `report property frame=0 > property.txt`
	// Source: https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
	std::string contentHand ;
	contentHand.assign( ( std::istreambuf_iterator<char>(propFile) ),
					( std::istreambuf_iterator<char>() )
				  );

	std::smatch matchBlockHand ;

	while (std::regex_search(contentHand, matchBlockHand, rgxSetHand))
	{
		std::cout << matchBlockHand.str(0) << std::endl ;
		contentHand = matchBlockHand.suffix() ;
	}

	std::string contentCouple ;
	contentCouple.assign( ( std::istreambuf_iterator<char>(propFile) ),
					( std::istreambuf_iterator<char>() )
				  );

	std::smatch matchBlockCouple ;

	while (std::regex_search(contentCouple, matchBlockCouple, rgxSetCouple))
	{
		std::cout << matchBlockCouple.str(0) << std::endl ;
		contentCouple = matchBlockCouple.suffix() ;
	}

	// std::cout << content << std::endl ;

	// If property file was opened successfully
	while (propFile)
	{
		// Declare empty string variable in which file line contents will be
		// temporarily stored
		std::string line ;

		// Read property file line-by-line
		while (std::getline(propFile, line))
		{
			std::smatch matchLine ;
			std::smatch matchNum ;

			// Check for hand sections
			if (std::regex_search(line, matchLine, rgxHandName))
			{
				std::cout << matchLine.str(0) << std::endl ;
			}


		}

		// std::string section ;
		//
		// if ( std::regex_search(line, matchLine, rgxUnload) )
		// {	// If line contains unloaded speed string
		// 	if ( std::regex_search(line, matchNum, rgxNum))
		// 		simul.unloadedSpeed = std::stof(matchNum.str(0));
		// }
		// else if ( std::regex_search(line, matchLine, rgxStall))
		// {	// If line contains stall force string
		// 	if (std::regex_search(line, matchNum, rgxNum))
		// 		simul.stallForce = std::stof(matchNum.str(0));
		// }

	}

	propFile.close() ;
}
