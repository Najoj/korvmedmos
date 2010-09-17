#include <iostream>

//Custom includes
#include "client.hpp"
#include "node.hpp"

using namespace std;



/**
 * Variabels.
 */

//Used for representing the entire board.
int board[200];


//Returns null if no child is avaible.
Node getChildState(Node *n);

void readBoard();
Node getChildState(Node *n){

	//n->getBoxes();

	return NULL;
}

void readBoard(){

	char *k;
	while(istream::get(k)){
		cout << "HEJ" << endl;
	}
//	while( cin >> k ){
	//	cout << "Read int: " << k << endl;
//	}
	//cout << " woot?";
}
int main(int argc, char ** argv)
{

	readBoard();
	/*
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
	*/
	return 0;
}
