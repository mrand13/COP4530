CC=gcc
#CXX=g++47
CXXFLAGS=-std=c++11 -Wall -pedantic

proj2.x: test_list.o List.h
	$(CXX) $(CXXFLAGS) -o $@ test_list.cpp

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