# Ugly makefile. :-)

all: client.hpp  main.cpp  node.cpp  node.hpp common.hpp
	g++ -lboost_system main.cpp node.cpp -o main

FORCE: client.hpp  main.cpp  node.cpp  node.hpp common.hpp
	g++ -fpermissive -lboost_system main.cpp -o main

clean: main
	rm main

help:
	cat Makefile
