#include "calculate.h"
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

	@param 	currentFrame		-	reference to Frame object
	@param	previousFrame		-	reference to Frame object
	@param	simul				- 	reference to Simul object, which contains data on simulation parameters

	*/
void calculate_frame(Frame & currentFrame, Frame & previousFrame, Simul & simul)
{
	//* Need to have at least one previousFrame to do calculations
	//* Number of linkers in current and previous frames should be non-zero
	if (currentFrame.frameNumber > 0 && currentFrame.numLinkers > 0 )
	{
		std::vector <Linker>::iterator linkerPtr = currentFrame.linkerObjects.begin(),
									   endPtr = currentFrame.linkerObjects.end() ;


		currentFrame.wDot = 0.0 ;

		printf("Frame number: %d\n", currentFrame.frameNumber) ;

		// Iterate through each linker in the frame
		do
		{
			Linker currentLinker = *linkerPtr ;

			// bool linkerExisted ;
			//
			// // Check if a specific linker was also doubly-linked in the previous frame
			// Linker pastLinker = check_linker_past(linkerExisted, currentLinker, previousFrame) ;

			if (true)
			{
				printf("--- Linker %d existed in previous frame, proceed with calculations\n",
					   currentLinker.linkerIdentity) ;

				// calculate_force_vector(currentLinker) ;

				// std::cout << "Force vectors:" << std::endl;
				// std::cout << currentLinker.handOne.forceVector << std::endl ;
				// std::cout << currentLinker.handTwo.forceVector << std::endl ;

				// calculate_direction_vector(currentLinker, pastLinker) ;

				// std::cout << "Direction vectors:" << std::endl ;
				// std::cout << currentLinker.handOne.directionVector << std::endl ;
				// std::cout << currentLinker.handTwo.directionVector << std::endl ;

				// calculate_velocity_vector(simul, currentLinker) ;

				// std::cout << "Velocity vectors:" << std::endl ;
				// std::cout << currentLinker.handOne.velocityVector <<std::endl ;
				// std::cout << currentLinker.handTwo.velocityVector << std::endl ;

				// calculate_linker_w_dot(currentLinker) ;

				// std::cout << "w dot for linker:" << std::endl ;
				// std::cout << currentLinker.wDot << std::endl ;

				//* Add linker wDot contribution to the running total for wDot for the frame
				// currentFrame.wDot += currentLinker.wDot ;
			}
			++linkerPtr ;
		} while (linkerPtr != endPtr) ;


	}
	else
		printf("Frame number: %d\n--- No linkers in current and/or previous frame\n",
			   currentFrame.frameNumber) ;

	// float dt = currentFrame.timeStamp - previousFrame.timeStamp ;
	// printf("dt is %f\n", dt) ;

	//* Add frame wDot contribution to the running total for wDot for the trajectory
	// simul.wDotIntegral += currentFrame.wDot * dt ;

	// printf("w dot integral for trajectory: %f\n", simul.wDotIntegral) ;
}

/**	@brief	Check if a particular linker appears in previous frame.

	@param	linkerExisted	-	bool confiriming/denying linker existence in previous frame
	@param 	linker			-	reference to Linker object
	@param	previousFrame	-	reference to Frame object

	@return oldFrameLinker	-	Linker object, most recent in iterator. This value is not used in calculation code if linkerExisted is false.
	*/
Linker check_linker_past(bool & linkerExisted, Linker & linker, Frame & previousFrame)
{
	std::vector <Linker>::iterator linkerPtr = previousFrame.linkerObjects.begin(),
								   endPtr = previousFrame.linkerObjects.end() ;

	Linker oldFrameLinker ;

	//* Iterate through the linkers in the previous frame and check for presence of specific linker identity
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
	See http://eigen.tuxfamily.org/ for documentation on the Eigen library.

	@param	vector 		-	std::vector <float>

	@return	eigenVec 	-	Eigen::MatrixXf

	*/
Eigen::VectorXf convert_std_vec_to_eigen_vec(std::vector <float> vector)
{
	//* https://stackoverflow.com/questions/11387370/how-can-i-safely-convert-unsigned-long-int-to-int
	unsigned long int vecSizeLongInt = vector.size() ;
	const int vecSizeInt = vecSizeLongInt & INT_MAX ; // needs the <climits> library

	//* https://stackoverflow.com/questions/17036818/initialise-eigenvector-with-stdvector
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

// /**	@brief	Calculate the (normalized!) direction vector of a hand using positions of two adjacent frames
//
// 	@param	currentLinker		-	reference to Linker object
// 	@param	pastLinker			-	reference to Linker object
// 	*/
// void calculate_direction_vector(Linker & currentLinker, Linker & pastLinker)
// {
// 	currentLinker.handOne.directionVector = (currentLinker.handOne.positionVector_eigen - pastLinker.handOne.positionVector_eigen).normalized();
//
// 	currentLinker.handTwo.directionVector = (currentLinker.handTwo.positionVector_eigen - pastLinker.handTwo.positionVector_eigen).normalized() ;
// }

/**	@brief	Calculate the (normalized!) vector between the two linker hands and
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
	float velocityMag ;

	float work = linker.handOne.forceVector.dot(linker.handOne.directionVector_eigen)
				+linker.handTwo.forceVector.dot(linker.handTwo.directionVector_eigen) ;

	velocityMag = simul.unloadedSpeed * (1 + work / simul.stallForce) ;

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
