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

// Root node. Goat r00t?
Node * root;

// Returns null if no child is avaible.
Node * getChildState(Node *n);

// Reads the board into matrix.
void readBoard(std::string);

Node * getChildState(Node *n){

	//n->getBoxes();

	return NULL;
}

/* XXX: Removeable?
void readBoard(){

}
*/
void printBoard()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
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
void readBoard(std::string boardIn)
{
	string::iterator iterator;
	iterator = boardIn.begin();

	//Get x - lenght of the board
	width = boardIn.find("\n");
	height = boardIn.length()/width;

	//Allocate memory for the board
	board = new int*[width];

	int x = 0, y = 0;
	
	int box = 0;    // Counting boxes.
	Position jens;  // Jens is the man.
	
	//Allocate memory for the first column.
	board[x] = new int[height];
	
	while(iterator != boardIn.end())
	{
		if(*iterator == '\n')
		{
			x++;
			y = 0;
			//New full column. Matrix hack.
			board[x] = new int[height];
		} else {
			//Assign the value from the board.
    		if(*iterator == BOX || *iterator == BOX_ONGOAL ) {
    		    // My name is Boxxy. Counts boxes so that we can allocate them later.
		       box++;
    		} else if(*iterator == JENS || *iterator == JENS_ONGOAL ) {
    		    // Got Jens?
    		    jens.x = x;
    		    jens.y = y;
//	    	    root->jens = jens:  // Saving position in root node.
    		}
    		board[x][y] = * iterator;
			y++;
		}		
		iterator++;
	}
	
	// Removes boxes from board because they are saved in the nodes.
//*     Neat comment hack. Remove first '/' to comment upcomming lines.
    Position * boxes = new Position[box];
	box = 0;
    for(int i = 0; i < x; i++)
	{
	    for(int j = 0; j < y; j++)
	    {
    	    if( board[i][j] != WALL || board[i][j] != FLOOR )   // Most of them will be
    	    {
    	        // Theese are saved in root node, the board should be the static stuff.
    	        if(board[i][j] == BOX)  // Normal box
    	        {
    	            board[i][j] = FLOOR;
                    boxes[box].x = i;
                    boxes[box].y = j;
                    box++;
                }
                else if(board[i][j] == JENS)    // Normal Jens
                {
	                board[i][j] = FLOOR;
                }
                else if(board[i][j] == BOX_ONGOAL)  // Box on goal (rare)
                {
	                board[i][j] = GOAL;
                    boxes[box].x = i;
                    boxes[box].y = j;
                    box++;
                }
                else if(board[i][j] == JENS_ONGOAL) // Jens on goal (rare)
                {
	                board[i][j] = GOAL;
                }
            }
        }
	}
//*/
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
	// XXX: Is this board solvable?
	string test = "#############\n#####  ######\n#####     ###\n#####    ####\n###### #  ###\n###### #    #\n#     $**** #\n# $#$ $ ... #\n#       #@. #\n##########  #\n#############";


	readBoard(test);
    // Mostly for debugging purposes.
	printBoard();
	
/*
    Todo here:
     * Parse board into a tree graph.
     * Search in tree.
     * Make the solution
     - Johan
*/

	std::string solution = ("U R R D U U L D L L U L L D R R R R L D D R U R U D L L U R");
	// skicka in lösning och skriv ut svar
	//send(*socket, solution);
	return 0;
}
