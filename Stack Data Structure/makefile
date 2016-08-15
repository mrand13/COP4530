CC=gcc
#CXX=g++47
CXXFLAGS=-std=c++11 -Wall -pedantic

proj3.x: in2post.cpp stack.h
	$(CXX) $(CXXFLAGS) -o $@ in2post.cpp

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.o *.x core.*

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<