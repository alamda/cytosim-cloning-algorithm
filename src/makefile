# Makefile for Cytosim Cloning Algorithm Executable

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -I.
DEPS_CALC = calculator.h frame.h hand.h linker.h parser.h simul.h

# ****************************************************
# Targets needed to bring the executable up to date

all: calculate launch control

parser.o: parser.cpp $(DEPS_CALC)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o : %.cpp $(DEPS_CALC)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

calculate: calculate_main.o calculator.o parser.o frame.o
	$(CXX) $(CXXFLAGS) -o calculate calculate_main.o calculator.o parser.o frame.o

launch.o: launch.cpp launch.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

launch: launch.o
	$(CXX) $(CXXFLAGS) -o launch launch.o

control_population.o: control_population.cpp control_population.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

control: control_population.o
	$(CXX) $(CXXFLAGS) -o control control_population.o
