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


		currentFrame.wDot = 0.0 ;

		printf("Frame number: %d\n", currentFrame.frameNumber) ;

		do
		{
			Linker currentLinker = *linkerPtr ;

			bool linkerExisted ;

			Linker pastLinker = check_linker_past(linkerExisted, currentLinker, previousFrame) ;

			if (linkerExisted)
			{
				printf("--- Linker %d existence in previous frame: %d\n",
					   currentLinker.linkerIdentity, linkerExisted) ;

				calculate_force_vector(currentLinker) ;

				// std::cout << "Force vectors:" << std::endl;
				// std::cout << currentLinker.handOne.forceVector << std::endl ;
				// std::cout << currentLinker.handTwo.forceVector << std::endl ;

				calculate_direction_vector(currentLinker, pastLinker) ;

				// std::cout << "Direction vectors:" << std::endl ;
				// std::cout << currentLinker.handOne.directionVector << std::endl ;
				// std::cout << currentLinker.handTwo.directionVector << std::endl ;

				calculate_velocity_vector(simul, currentLinker) ;

				// std::cout << "Velocity vectors:" << std::endl ;
				// std::cout << currentLinker.handOne.velocityVector <<std::endl ;
				// std::cout << currentLinker.handTwo.velocityVector << std::endl ;

				calculate_linker_w_dot(currentLinker) ;
				std::cout << "w dot for linker:" << std::endl ;
				std::cout << currentLinker.wDot << std::endl ;

				currentFrame.wDot += currentLinker.wDot ;
			}
			++linkerPtr ;
		} while (linkerPtr != endPtr) ;


	}
	else
		printf("Frame number: %d\n--- No linkers in current and/or previous frame\n",
			   currentFrame.frameNumber) ;

	float dt = currentFrame.timeStamp - previousFrame.timeStamp ;
	printf("dt is %f\n", dt) ;
	simul.wDotIntegral += currentFrame.wDot * dt ;

	printf("w dot integral for trajectory: %f\n", simul.wDotIntegral) ;
}

/**	@brief	Check if a particular linker appears in previous frame.

	@param 	linker			-	reference to Linker object
	@param	previousFrame	-	reference to Frame object

	@return linkerExisted	-	bool confirming/denying that a linker was documented in the previous frame. Returns true if linker existed in previous frame.
	*/
Linker check_linker_past(bool & linkerExisted, Linker & linker, Frame & previousFrame)
{
	std::vector <Linker>::iterator linkerPtr = previousFrame.linkerObjects.begin(),
								   endPtr = previousFrame.linkerObjects.end() ;

	Linker oldFrameLinker ;

	do
	{
		oldFrameLinker = *linkerPtr ;

		linkerExisted = (linker.linkerIdentity == oldFrameLinker.linkerIdentity) ;
		++linkerPtr ;
	} while (!linkerExisted && linkerPtr != endPtr) ;

	return oldFrameLinker ;
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
void calculate_direction_vector(Linker & currentLinker, Linker & pastLinker)
{
	currentLinker.handOne.directionVector = currentLinker.handOne.positionVector_eigen - pastLinker.handOne.positionVector_eigen ;

	currentLinker.handTwo.directionVector = currentLinker.handTwo.positionVector_eigen - pastLinker.handTwo.positionVector_eigen ;
}

/**	@brief	Calculate the vector between the two linker hands.

	@param	linker			-	reference to Linker object
	*/
void calculate_force_vector(Linker & linker)
{
	Eigen::VectorXf handOneVec = linker.handOne.positionVector_eigen ;
	Eigen::VectorXf handTwoVec = linker.handTwo.positionVector_eigen ;

	linker.handOne.forceVector = (handTwoVec - handOneVec).normalized()*linker.force ;
	linker.handTwo.forceVector = (handOneVec - handTwoVec).normalized()*linker.force ;
}

/**	@brief Calculate the velocity magnitude of a hand of a linker for a given frame

	@todo	write this function

	*/
void calculate_velocity_vector(Simul & simul, Linker & linker)
{
	float velocityMag ;

	float work = linker.handOne.forceVector.dot(linker.handOne.directionVector)
				+linker.handTwo.forceVector.dot(linker.handTwo.directionVector) ;

	velocityMag = simul.unloadedSpeed * (1 + work / simul.stallForce) ;

	linker.handOne.velocityVector = linker.handOne.directionVector*velocityMag ;
	linker.handTwo.velocityVector = linker.handTwo.directionVector*velocityMag ;

}

/**	@brief Calculate the rate of work for a given frame

	@todo	write this function

	*/
void calculate_linker_w_dot(Linker & linker)
{
	linker.wDot = linker.handOne.forceVector.dot(linker.handOne.velocityVector)
				+ linker.handTwo.forceVector.dot(linker.handTwo.velocityVector) ;
}
