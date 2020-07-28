#ifndef CALCULATE_H
#define CALCULATE_H

#include "frame.h"
#include "simul.h"

#include <vector>

#include "Eigen/Dense"


Eigen::MatrixXf convert_std_vec_to_eigen_vec(std::vector <float> vector) ;

void calculate_velocity(Simul & simul) ;

void calculate_w_dot(Frame currentFrame, Frame previousFrame) ;

#endif // CALCULATE_H
