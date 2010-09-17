#include <iostream>

//Custom includes
#include "client.hpp"
#include "node.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	std::string lHost,lPort,lBoard;
	if(argc==4)
	{
		lHost = std::string(argv[1]);
		lPort = std::string(argv[2]);
		lBoard = std::string(argv[3]);
	}
	else if (argc==2)
	{
		lHost = std::string("cvap103.nada.kth.se");
		lPort = std::string("5555");
		lBoard = std::string(argv[1]);
	}
	else
	{
        std::cerr << "Usage: client (<host> <port>) <board2Solve>" << std::endl;
        return 1;
	}
	std::string solution=("U R R D U U L D L L U L L D R R R R L D D R U R U D L L U R");
	//Skicka svar till survurn.
	send(lHost, lPort, lBoard, solution);
	return 0;
}
