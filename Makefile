# Makefile for Autocorelation

all: main.cpp
	icpc -o main.o main.cpp

test: Test.cpp
	icpc -o test.o Test.cpp

clean:
	rm -rf *.o
