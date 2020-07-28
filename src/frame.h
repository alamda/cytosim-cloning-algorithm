#ifndef FRAME_H
#define FRAME_H

#include "linker.h"

#include <string>
#include <vector>

/**	@brief Struct for containing data for a single frame of the simulation.
	*/

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

	int numLinkers ;

	// Values that are calculated
	float wDot ;
} Frame_t ;

#endif // FRAME_H
