# set the directory of the Eigen library
set(EIGEN_DIR ${PROJECT_SOURCE_DIR}/lib/eigen-3.3.7)

add_executable(calc_traj_work
	main.cpp
	calculator.cpp
	calculator.h
	couple_prop.h
	frame.cpp
	frame.h
	hand_prop.h
	hand.h
	linker.h
	parser.cpp
	parser.h
	simul.h
	)

target_include_directories(calc_traj_work PUBLIC ${EIGEN_DIR})
