#include "calculate.h"
#include "frame.h"
#include "linker.h"
#include "head.h"
#include "simul.h"
#include <cstdio>
#include "Eigen/Dense"
#include <vector>
#include <climits>
#include <iostream>


Eigen::MatrixXf convert_std_vec_to_eigen_vec(std::vector <float> vector)
{
	// https://stackoverflow.com/questions/11387370/how-can-i-safely-convert-unsigned-long-int-to-int
	unsigned long int vec_size_long_int = vector.size() ;
	const int vec_size_int = vec_size_long_int & INT_MAX ;

	// https://stackoverflow.com/questions/52261389/how-to-convert-an-stdvector-to-a-matrix-in-eigen
	Eigen::MatrixXf eigen_vec ;

	if (vec_size_int == 2)
		eigen_vec = Eigen::Map<Eigen::Matrix <float, 2, 1> > (vector.data()) ;
	else if (vec_size_int == 3)
		eigen_vec = Eigen::Map<Eigen::Matrix <float, 3, 1> > (vector.data()) ;
	else
		std::cout << "Your dimensions are weird, try either 2D or 3D." << std::endl ;

	return eigen_vec  ;
}

void calculate_velocity(Simulation & simul)
{

}

void calculate_w_dot(Frame currentFrame, Frame previousFrame)
{
	// for (linker : currentFrame)
	//		if linker.linkerIdentity also appears in previousFrame
	//			do calculations
	//			store in vector ??
}
