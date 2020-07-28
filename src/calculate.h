#ifndef CALCULATE_H
#define CALCULATE_H

#include "frame.h"
#include "linker.h"
#include "simul.h"

#include <vector>

#include "Eigen/Dense"

void calculate_frame(Frame & currentFrame, Frame & previousFrame, Simul & simul) ;

Linker check_linker_past(bool & linkerExisted, Linker & linker, Frame & previousFrame) ;

Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector) ;

void calculate_direction_vector(Linker & currentLinker, Linker & pastLinker) ;

void calculate_force_vector(Linker & linker) ;

void calculate_velocity_vector(Simul & simul, Linker & linker) ;

void calculate_linker_w_dot(Linker & linker) ;

#endif // CALCULATE_H
