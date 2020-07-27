#ifndef CALCULATE_H
#define CALCULATE_H

#include "Eigen/Dense"
#include <vector>
#include "simul.h"
#include "frame.h"

Eigen::MatrixXf convert_std_vec_to_eigen_vec(std::vector <float> vector) ;

void calculate_velocity(Simulation & simul) ;

void calculate_w_dot(Frame currentFrame, Frame previousFrame) ;

#endif // CALCULATE_H
