# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o simul.o frame.o head.o linker.o calculate.o parse.o
	$(CXX) $(CXXFLAGS) -o main main.o simul.o frame.o head.o linker.o calculate.o parse.o

# The main.o target can be written more simply

main.o: main.cpp parse.h
	$(CXX) $(CXXFLAGS) -c main.cpp

simul.o: simul.cpp simul.h

frame.o: frame.cpp frame.h linker.h

head.o: head.cpp head.h

linker.o: linker.cpp linker.h head.h

calculate.o: calculate.cpp calculate.h simul.h frame.h linker.h

parse.o: parse.cpp parse.h frame.h simul.h
