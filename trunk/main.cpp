#include <iostream>
#include "client.hpp"
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
	send(lHost, lPort, lBoard);
	return 0;
}
