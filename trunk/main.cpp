#include <iostream>
#include <boost/asio.hpp>
#include <boost/multi_array.hpp>

//Custom includes
#include "client.hpp"
#include "node.hpp"

using namespace std;

/**
 * Variabels.
 */

//Used for representing the entire board.
int **board;

//Width and height of the board.
int width, height;

//Returns null if no child is avaible.
Node * getChildState(Node *n);

void readBoard(std::string);

Node * getChildState(Node *n){

	//n->getBoxes();

	return NULL;
}

void readBoard(){

}
void printBoard(){
	for(int i = 0; i < height; i++){
		for(int j=0;j < width; j++){
			cout << (char) board[i][j] << "";
		}
		cout << endl;
	}
}
/**
 * Reads the board into a int matrix called board (global var)
 * @param string The String representing the board.
 */
//Varför ska denna ha &-argument?
// Vad är ett &-argument? - Johan
void readBoard(std::string boardIn){
	string::iterator iterator;
	iterator = boardIn.begin();

	//Get x - lenght of the board
	width = boardIn.find("\n");
	height = boardIn.length()/width;

	//Allocate memory for the board
	board = new int*[width];



	int x = 0, y = 0;
	
	//Allocate memory for the first column.
	board[x] = new int[height];
	
	while(iterator != boardIn.end()){

		if(*iterator == '\n'){
			x++;
			y = 0;
			//New full column. Matrix hack.
			board[x] = new int[height];
		}else{
			//Assign the value from the board.
			board[x][y] =  *iterator;
			y++;
		}
		iterator++;

	}

}

int main(int argc, char ** argv)
{


	// Command-line argument handling
/*  // Set or remove / at the beginning of this line to uncomment or comment following 18 lines
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
        std::cerr << "Usage: main (<host> <port>) <board2Solve>" << std::endl;
        return 1;
	}
//  */
	
	// öppna socket som håller connection till server
	//boost::asio::ip::tcp::socket * socket = open(lHost, lPort);

	/**
	 * W000T?
	 */
	// välj board lBoard och läs in från server
	//std::string board = read(*socket, lBoard);
	//read(NULL,NULL);
	


	//***** HERE IS ACTION *****
	//readBoard(board);
	string test = "#############\n#####  ######\n#####     ###\n#####    ####\n###### #  ###\n###### #    #\n#     $**** #\n# $#$ $ ... #\n#       #@. #\n##########  #\n#############";


	readBoard(test);
	printBoard();

	std::string solution = ("U R R D U U L D L L U L L D R R R R L D D R U R U D L L U R");
	// skicka in lösning och skriv ut svar
	//send(*socket, solution);

	return 0;
}
