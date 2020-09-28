# set the directory of the Eigen library
set(EIGEN_DIR ${PROJECT_SOURCE_DIR}/lib/eigen-3.3.7)

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

target_include_directories(calculate PUBLIC ${EIGEN_DIR})

