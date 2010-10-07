# Ugly makefile. :-)

all:  main.cpp node.cpp rules.cpp Board.hpp client.hpp common.hpp hash_functions.hpp heuristics.hpp node.hpp rules.hpp
	g++ -lboost_system -lpthread  main.cpp node.cpp rules.cpp  -o main

clean: main
	rm main

help:
	cat Makefile
