#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include "parse_output.h"

// Used as reference: https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
bool get_file_contents( std::string fileName, std::vector<std::string> & vectorOfFileLines )
{
	// open file
	std::ifstream file(fileName.c_str());

	// Check if object is valid
	if(!file)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}

	// Define string variable
	std::string str ;

	// Read the next line from File untill it reaches the end.
	while (std::getline(file, str))
	{
		// Line contains string of length > 0 then save it in vector
		if(str.size() > 0)
			vectorOfFileLines.push_back(str);
	}

	//Close The File
	file.close();

	return true;
}

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


void split_frames(std::vector<std::string> & vectorOfFileLines,
				  std::vector <std::vector <std::string> > & vectorOfFrames,
				  std::vector <Frame> & vectorOfFrameObjects,
				  std::string const startSubstring,
				  std::string const endString )
{
	// define vector for storing content of a single frames
	std::vector <std::string> vectorOfFrameContent;

	// Iterate over each line in the file
	for(std::string & line : vectorOfFileLines)
	{
		// check if the line contains the string denoting the start of the frame
		std::size_t found = line.find(startSubstring);

		// if start substring is found in the line
		if (found != std::string::npos)
		{
			// empty out the vector of frame content
			vectorOfFrameContent.clear() ;

			printf("start of frame\n");
		}

		vectorOfFrameContent.push_back(line);

		// check if the line contains the string denoting the end of the frame
		found = line.find(endString);

		if (found != std::string::npos)
		{
			vectorOfFrames.push_back(vectorOfFrameContent);

			printf("end of frame, number of lines for frame is %d\n\n",
					vectorOfFrameContent.size());

			process_frame(vectorOfFrameContent, vectorOfFrameObjects);
		}
	}

	printf("end of file parsing, number of frames is %d\n\n", vectorOfFrames.size());

	printf("%c\n", *vectorOfFrames.end());

}




int main()
{
	// define vector for storing lines extracted from file
	std::vector <std::string> vectorOfFileLines;

	// define vector for storing frames which store lines corresponding to the frames
	std::vector <std::vector <std::string> >  vectorOfFrames;

	std::vector <Frame> vectorOfFrameObjects ;


	// Get the contents of file in a vector
	// vectorOfLines is modified by the function because one of the arguments
	// is actually defined to be a reference to vectorOfLines ???
	bool result = get_file_contents("link.txt", vectorOfFileLines);

	// Specify strings at start and end of file
	const std::string startSubstring = "% frame";
	const std::string endString = "% end";

	// Check that the file exists/is valid
	if(result)
	{
		// Pass a pointer to vectorOfFrames, everything else unchanged
		split_frames(vectorOfFileLines, vectorOfFrames, vectorOfFrameObjects, startSubstring, endString);
	}



	return 0;
}
