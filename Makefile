# Ugly makefile. :-)

all: client.hpp  main.cpp  node.cpp  node.hpp
	g++ -lboost_system main.cpp -o main

FORCE: client.hpp  main.cpp  node.cpp  node.hpp
	g++ -fpermissive -lboost_system main.cpp -o main

clean: main
	rm main

help:
	cat Makefile
