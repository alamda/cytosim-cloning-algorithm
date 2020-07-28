#include "calculate.h"
#include "frame.h"
#include "simul.h"

#include <climits>
#include <vector>

#include "Eigen/Dense"

/**	@brief	Convert std::vector to Eigen::MatrixXf for snappy maths.

	Works with 2- or 3-dimensional vectors, other dimensions not supported.

	@param	vector 		-	std::vector <float>
	@return	eigen_vec 	-	Eigen::MatrixXf

	*/
Eigen::MatrixXf convert_std_vec_to_eigen_vec(std::vector <float> vector)
{
	// https://stackoverflow.com/questions/11387370/how-can-i-safely-convert-unsigned-long-int-to-int
	unsigned long int vec_size_long_int = vector.size() ;
	const int vec_size_int = vec_size_long_int & INT_MAX ; // needs the <climits> library

	// https://stackoverflow.com/questions/52261389/how-to-convert-an-stdvector-to-a-matrix-in-eigen
	Eigen::MatrixXf eigen_vec ;

	if (vec_size_int == 2)
		eigen_vec = Eigen::Map<Eigen::Matrix <float, 2, 1> > (vector.data()) ;
	else if (vec_size_int == 3)
		eigen_vec = Eigen::Map<Eigen::Matrix <float, 3, 1> > (vector.data()) ;
	else
		printf("Your dimensions are weird, try either 2D or 3D.\n") ;

	return eigen_vec  ;
}

/**	@brief Calculate the velocity of a head of a linker for a given frame

	@todo	write this function

	*/
void calculate_velocity(Simul & simul)
{

}

/**	@brief Calculate the rate of work for a given frame

	@todo	write this function

	*/
void calculate_w_dot(Frame currentFrame, Frame previousFrame)
{
	// for (linker : currentFrame)
	//		if linker.linkerIdentity also appears in previousFrame
	//			do calculations
	//			store in vector ??
}
