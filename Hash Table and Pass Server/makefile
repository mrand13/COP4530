CC=gcc
#CXX=g++47
CXXFLAGS=-std=c++11 -Wall -pedantic -lcrypt

proj5.x: proj5.o passserver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

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