#ifndef PARSE_H
#define PARSE_H

#include <string>
#include "frame.h"
#include "simul.h"

void process_line(std::string line, Frame & frame) ;

bool check_dimension(Frame & frame) ;

void process_frame(Frame & frame) ;

void get_output_file_contents( std::string fileName, Simul & simul ) ;


#endif // PARSE_H
