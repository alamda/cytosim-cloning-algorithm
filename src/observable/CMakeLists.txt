#add_executable(calcualte main.cpp)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)


find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(calculate 
	main.cpp
	parser.cpp
	parser.h
	calculator.cpp
	calculator.h
	frame.cpp
	frame.h
	hand.h
	linker.h
	simul.h
	)

