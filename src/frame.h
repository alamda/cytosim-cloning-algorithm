#ifndef FRAME_H
#define FRAME_H

#include "linker.h"

#include <string>
#include <vector>

/**	@brief Struct for containing data for a single frame of the simulation.
	*/

typedef struct Frame_s
{
	int frameNumber ;
	const static std::string frameStr ;

	float timeStamp ;
	const static std::string timeStr ;

	std::string reportCommand ;
	const static std::string reportStr ;

	std::vector <std::string> dataCategories ;
	const static std::string categoriesStr ;

	std::vector <std::vector <std::string> > dataLines;

	const static std::string endStr ;

	std::vector <Linker> linkerObjects ;

	int numLinkers ;

	// Values that are calculated
	float wDot = 0.0;
	float dt ;
} Frame ;

#endif // FRAME_H
