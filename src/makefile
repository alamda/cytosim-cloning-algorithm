# Makefile for Cytosim Cloning Algorithm Executable

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -I.
DEPS = calculate.h frame.h hand.h linker.h parse.h simul.h

# ****************************************************
# Targets needed to bring the executable up to date

%.o : %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: main.o calculate.o parse.o
	$(CXX) $(CXXFLAGS) -o main main.o calculate.o parse.o
