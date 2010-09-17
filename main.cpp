#include <iostream>
#include <boost/asio.hpp>

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
Node * getChildState(Node *n);

void readBoard(std::string);

Node * getChildState(Node *n){

	//n->getBoxes();

	return NULL;
}

void readBoard(std::string& board){
	for(unsigned int i=0; i < board.size(); i++){
		cout << "HEJ" << endl;
	}
}

int main(int argc, char ** argv)
{
	// Command-line argument handling
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
	
	// öppna socket som håller connection till server
	boost::asio::ip::tcp::socket * socket = open(lHost, lPort);
	// välj board lBoard och läs in från server
	std::string board = read(*socket, lBoard);
	
	cout << board;

	//***** HERE IS ACTION *****
	//readBoard(board);
	
	std::string solution=("U R R D U U L D L L U L L D R R R R L D D R U R U D L L U R");
	// skicka in lösning och skriv ut svar
	send(*socket, solution);

	return 0;
}
