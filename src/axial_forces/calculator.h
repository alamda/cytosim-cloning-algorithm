#ifndef CALCULATE_H
#define CALCULATE_H

#include "frame.h"
#include "linker.h"
#include "simul.h"
#include "fiber.h"

#include <vector>

#include "Eigen/Dense"

void calculate_frame(Simul & simul, Frame & frame) ;

Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector) ;

void calculate_force_vector(Linker & linker) ;

void calculate_velocity_vector(Simul & simul, Linker & linker) ;

void calculate_fiber_observable(Fiber & fiber) ;

void find_largest_cluster(Frame & frame) ;
#endif // CALCULATE_H
