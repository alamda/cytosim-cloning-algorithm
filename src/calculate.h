#ifndef CALCULATE_H
#define CALCULATE_H

#include "frame.h"
#include "linker.h"
#include "simul.h"

#include <vector>

#include "Eigen/Dense"

void calculate_frame(Frame & currentFrame, Frame & previousFrame, Simul & simul) ;

bool check_linker_past(Linker & linker, Frame & previousFrame) ;

Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector) ;

void calculate_force_vector(Linker & linker) ;

float calculate_velocity(Simul & simul) ;

void calculate_w_dot(Frame currentFrame, Frame previousFrame) ;

#endif // CALCULATE_H
