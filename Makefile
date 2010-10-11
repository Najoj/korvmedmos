# Ugly makefile. :-)

# Everything
all:  main.cpp node.cpp rules.cpp Board.hpp client.hpp common.hpp heuristics.hpp node.hpp rules.hpp
	g++ -p -O3  -lboost_system -lpthread  main.cpp node.cpp rules.cpp  -o main

# Show all warnings
Wall:  main.cpp node.cpp rules.cpp Board.hpp client.hpp common.hpp heuristics.hpp node.hpp rules.hpp
	g++ -Wall -p -O3  -lboost_system -lpthread  main.cpp node.cpp rules.cpp  -o main

# Why do we even have this?
clean: main
	rm main

# If this does not help you, please do not use a computer.
help:
	cat Makefile
