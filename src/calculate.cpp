#include "calculate.h"
#include "frame.h"
#include "linker.h"
#include "simul.h"

#include <climits>
#include <iostream>
#include <vector>

#include "Eigen/Dense"

/**	@brief	Do calculations on a frame

	@param 	currentFrame		-	reference to Frame object
	@param	previousFrame		-	reference to Frame object
	@param	simul				- 	reference to Simul object, which contains data on simulation parameters

	*/
void calculate_frame(Frame & currentFrame, Frame & previousFrame, Simul & simul)
{
	if (currentFrame.frameNumber > 0 && currentFrame.numLinkers > 0 && previousFrame.numLinkers > 0)
	{
		std::vector <Linker>::iterator linkerPtr = currentFrame.linkerObjects.begin(),
									   endPtr = currentFrame.linkerObjects.end() ;

		printf("Frame number: %d\n", currentFrame.frameNumber) ;

		do
		{
			Linker currentLinker = *linkerPtr ;

			bool linkerExisted = check_linker_past(currentLinker, previousFrame) ;

			calculate_force_vector(currentLinker) ;

			printf("--- Linker %d existence in previous frame: %d\n",
				   currentLinker.linkerIdentity, linkerExisted) ;

			std::cout << currentLinker.handOne.forceVector << std::endl ;
			std::cout << currentLinker.handTwo.forceVector << std::endl ;

			++linkerPtr ;
		} while (linkerPtr != endPtr) ;

		// do calculations on frame and previousFrame
		calculate_velocity(simul) ;

		// calculations will be done by function calculate_w_dot()

		calculate_w_dot(currentFrame, previousFrame);
	}
	else
		printf("Frame number: %d\n--- No linkers in current and/or previous frame\n",
			   currentFrame.frameNumber) ;

	printf("\n") ;
}

/**	@brief	Check if a particular linker appears in previous frame.

	@param 	linker			-	reference to Linker object
	@param	previousFrame	-	reference to Frame object

	@return linkerExisted	-	bool confirming/denying that a linker was documented in the previous frame. Returns true if linker existed in previous frame.
	*/
bool check_linker_past(Linker & linker, Frame & previousFrame)
{
	bool linkerExisted ;

	std::vector <Linker>::iterator linkerPtr = previousFrame.linkerObjects.begin(),
								   endPtr = previousFrame.linkerObjects.end() ;

	do
	{
		Linker oldFrameLinker = *linkerPtr ;

		linkerExisted = (linker.linkerIdentity == oldFrameLinker.linkerIdentity) ;
		++linkerPtr ;
	} while (!linkerExisted && linkerPtr != endPtr) ;

	return linkerExisted ;
}

/**	@brief	Convert std::vector to Eigen::MatrixXf for snappy maths.

	Works with 2- or 3-dimensional vectors, other dimensions not supported.

	@param	vector 		-	std::vector <float>
	@return	eigenVec 	-	Eigen::MatrixXf

	*/
Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector)
{
	// https://stackoverflow.com/questions/11387370/how-can-i-safely-convert-unsigned-long-int-to-int
	unsigned long int vecSizeLongInt = vector.size() ;
	const int vecSizeInt = vecSizeLongInt & INT_MAX ; // needs the <climits> library

	// https://stackoverflow.com/questions/17036818/initialise-eigenvector-with-stdvector
	Eigen::VectorXf eigenVec ;

	if (vecSizeInt == 2)
	{
		Eigen::Map<Eigen::Vector2f> eigenVec(vector.data()) ;
		return eigenVec  ;
	}
	else if (vecSizeInt == 3)
	{
		Eigen::Map<Eigen::Vector3f> eigenVec(vector.data()) ;
		return eigenVec  ;
	}
	else
	{
		printf("Your dimensions are weird, try either 2D or 3D.\n") ;
		Eigen::VectorXf eigenVec ;
		return  eigenVec ;
	}
}

/**	@brief	Calculate the direction vector of a hand using positions of two adjacent frames

	@todo	Write this function
	@todo	add to calculate.h once written
	*/
void calculate_direction_vector(Frame & currentFrame, Frame & previousFrame)
{

}

/**	@brief	Calculate the vector between the two linker hands.

	@param	linker			-	reference to Linker object

	@todo	Write this function
	*/
void calculate_force_vector(Linker & linker)
{
	Eigen::VectorXf handOneVec = convert_std_vec_to_eigen_vec(linker.handOne.positionVector) ;
	Eigen::VectorXf handTwoVec = convert_std_vec_to_eigen_vec(linker.handTwo.positionVector) ;

	linker.handOne.forceVector = handTwoVec - handOneVec ;
	linker.handTwo.forceVector = handOneVec - handTwoVec ;
}

/**	@brief Calculate the velocity magnitude of a hand of a linker for a given frame

	@todo	write this function

	*/
float calculate_velocity(Simul & simul)
{
	float velocity ;



	velocity = simul.unloadedSpeed * (1 + 0 / simul.stallForce) ;


	return velocity ;
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
