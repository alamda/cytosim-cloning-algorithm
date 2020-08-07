#ifndef PARSER_H
#define PARSER_H

#include "frame.h"
#include "simul.h"

#include <string>

void process_line(std::string & line, Frame & frame) ;

void process_frame(Simul & simul, Frame & frame) ;

void process_data_file( Simul & simul, std::string dataFileName, std::string wDotsFileName, std::string wDotIntegralFileName ) ;

#endif // PARSER_H
