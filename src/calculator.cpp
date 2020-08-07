#include "calculator.h"
#include "frame.h"
#include "linker.h"
#include "simul.h"

#include <climits>
#include <iostream>
#include <vector>

#include "Eigen/Dense"

/**	@brief	Do calculations on a frame for each eligible* linker.

	*Eligible linkers are those that are both present in the current frame and in the previous frame.
	Calculations include:
	- Calculate the force vector on each hand for a linker
	- Calculate the direction vector for each hand
	- Calculate the velocity vector for each hand
	- Calculate the wDot contribution from the linker
	- Add wDot contribution from all linkers in the frame to the wDot value for the trajectory

	@param 	frame		-	reference to Frame object
	@param	simul				- 	reference to Simul object, which contains data on simulation parameters

	*/
void calculate_frame(Simul & simul, Frame & frame)
{
	//* Number of linkers in current frame should be non-zero
	if (frame.numLinkers > 0 )
	{
		std::vector <Linker>::iterator linkerPtr = frame.linkerObjects.begin(),
									   endPtr = frame.linkerObjects.end() ;

		// Set wDot for frame to zero, will be adding linker wDot values to it
		frame.wDot = 0.0 ;

		// printf("Frame number: %d\n", frame.frameNumber) ;

		// Iterate through each linker in the frame
		do
		{
			// Dereference the linker pointer
			Linker currentLinker = *linkerPtr ;

			// std::cout << currentLinker.handOne.directionVector_eigen << std::endl ;

			calculate_force_vector(currentLinker) ;

			// make sure to add #include <iostream> if uncommenting below lines

			// std::cout << "Force vectors:" << std::endl;
			// std::cout << currentLinker.handOne.forceVector << std::endl ;
			// std::cout << currentLinker.handTwo.forceVector << std::endl ;
			//
			// std::cout << "Direction vectors:" << std::endl ;
			// std::cout << currentLinker.handOne.directionVector_eigen << std::endl ;
			// std::cout << currentLinker.handTwo.directionVector_eigen << std::endl ;

			calculate_velocity_vector(simul, currentLinker) ;

			// std::cout << "Velocity vectors:" << std::endl ;
			// std::cout << currentLinker.handOne.velocityVector <<std::endl ;
			// std::cout << currentLinker.handTwo.velocityVector << std::endl ;

			calculate_linker_w_dot(currentLinker) ;

			// std::cout << "w dot for linker: " << currentLinker.wDot<<std::endl ;

			//* Add linker wDot contribution to the running total for wDot for the frame
			frame.wDot += currentLinker.wDot ;

			// Increment the linker pointer (go to next linker in frame)
			++linkerPtr ;
		} while (linkerPtr != endPtr) ;
	}
	// else
	// 	printf("Frame number: %d\n--- No linkers in current and/or previous frame\n",
	// 		   frame.frameNumber) ;

	// printf("wDot for frame is %f\n", frame.wDot) ;

	//* Add frame wDot contribution to the running total for wDot for the trajectory
	simul.wDotIntegral += frame.wDot * frame.dt ;
}

/**	@brief	Convert std::vector to Eigen::MatrixXf for snappy maths.

	Works with 2- or 3-dimensional vectors, other dimensions not supported.
	See http://eigen.tuxfamily.org/ for documentation on the Eigen library.

	@param	vector 		-	std::vector <float>

	@return	eigenVec 	-	Eigen::MatrixXf

	*/
Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector)
{
	// Convert vector size from unsigned long to int
	//* See https://stackoverflow.com/questions/11387370/how-can-i-safely-convert-unsigned-long-int-to-int
	unsigned long int vecSizeLongInt = vector.size() ;
	const int vecSizeInt = vecSizeLongInt & INT_MAX ; // needs the <climits> library

	//* https://stackoverflow.com/questions/17036818/initialise-eigenvector-with-stdvector

	// It is very important that the returns are in the if statements! 

	if (vecSizeInt == 2)
	{
		Eigen::Map<Eigen::Vector2f> eigenVec(vector.data()) ;
		return eigenVec ;
	}
	else if (vecSizeInt == 3)
	{
		Eigen::Map<Eigen::Vector3f> eigenVec(vector.data()) ;
		return eigenVec ;
	}
	else
	{
		Eigen::VectorXf eigenVec ;
		printf("Your dimensions are weird, try either 2D or 3D.\n") ;
		return eigenVec ;
	}
}

/**	@brief	Calculate the vector between the two linker hands and
			multiply by the force between them to obtain the force vector.

	@param	linker			-	reference to Linker object
	*/
void calculate_force_vector(Linker & linker)
{
	Eigen::VectorXf handOneVec = linker.handOne.positionVector_eigen ;
	Eigen::VectorXf handTwoVec = linker.handTwo.positionVector_eigen ;

	linker.handOne.forceVector = (handTwoVec - handOneVec).normalized()*linker.force ;
	linker.handTwo.forceVector = (handOneVec - handTwoVec).normalized()*linker.force ;
}

/**	@brief Calculate the velocity vector of a hand of a linker for a given frame

	First, calculate the velocity magnitude:
	$v = v_0 (1 + \vec{f}\cdot\vec{d}/f_0)$
	Then, multiply the direction vector by the calculated magnitude.

	@param	simul		-	reference to Simul object
	@param	linker		-	reference to Linker object

	*/
void calculate_velocity_vector(Simul & simul, Linker & linker)
{
	// The work for the linker is the sum of the work done by each linker hand
	float work = linker.handOne.forceVector.dot(linker.handOne.directionVector_eigen)
				+linker.handTwo.forceVector.dot(linker.handTwo.directionVector_eigen) ;

	// Calcuate the magnitude of the velocity
	float velocityMag = simul.unloadedSpeed * (1 + work / simul.stallForce) ;

	linker.handOne.velocityVector = linker.handOne.directionVector_eigen*velocityMag ;
	linker.handTwo.velocityVector = linker.handTwo.directionVector_eigen*velocityMag ;
}

/**	@brief Calculate the rate of work for a given frame

	$\dot{w} = \vec{f}\cdot\vec{v}$

	@param	linker		-	reference to Linker object

	*/
void calculate_linker_w_dot(Linker & linker)
{
	//* wDot for the linker is the sum of wDot contributions from each linker hand
	linker.wDot = linker.handOne.forceVector.dot(linker.handOne.velocityVector)
				+ linker.handTwo.forceVector.dot(linker.handTwo.velocityVector) ;
}
