#include <iostream>
#include <boost/asio.hpp>
#include <boost/multi_array.hpp>
#include <vector>
#include <stack>

//Custom includes
#include "client.hpp"
#include "node.hpp"

using namespace std;

/**
 * Variables.
 */
int ** board;        // Used for representing the entire board.
int width, height;  // Width and height of the board.
vector<Position> boxes; //Ze boxes
vector<Position> goal_positions;
Node * root;        // Root node.
Node * getChildState(Node *n);  // Returns null if no child is avaible.

/**
 * Methods
 */
Node * readBoard(std::string);    // Reads the board into matrix.

/**
 * Fecthes child of root n.
 */
Node * getChildState(Node *n){
	//n->getBoxes();
	return NULL;
}

/**
 * Prints the board based on the board global variable.
 */
void printBoard()
{
	cout << "H: "<< height << " W:" << width<<endl;
	for(int j = 0; j < height; j++)
	{
		for(int i = 0; i < width; i++)
		{
			cout << (unsigned char) board[i][j] << "";
		}
		cout << endl;
	}
}

/**
 * Reads the board into a int matrix called board (global var)
 * @param string The String representing the board.
 */
Node * readBoard(std::string boardIn)
{
    // Creates an iterator.
	string::iterator iterator;
	iterator = boardIn.begin();

	//Get the lenght of the board. Which is the position of first '\n'.
	width = boardIn.find("\n");
	// Height is then the total length of the string, divide with the height.
	height = boardIn.length() / width;
	cout << "H: "<< height << " W:" << width<<endl;

	//Allocate memory for the board
	//board = new int*[width];

    // Koskenkorva.
	int x = 0, y = 0;
	
	int box = 0;    // Counting boxes.
	Position jens;  // Jens is the man, this is his position. Will be in root.
	
	//Allocate memory for the first column.
	board = new int*[width];
	for (int i = 0; i < width; i++)
		board[i] = new int[height];
	
	while(iterator != boardIn.end())
	{
		if(*iterator == '\n')
		{
			// if newline add y (column)
			y++;
			x = 0;
		} else {
    		Position p;
    		switch (*iterator) {
				case BOX:
					p.x = x;
					p.y = y;
					boxes.push_back(p);
					board[x][y] = 		FLOOR;
					break;
				case JENS:
					jens.x = x;
					jens.y = y;
					board[x][y] = FLOOR;
					break;
				case BOX_ONGOAL:
					p.x = x;
					p.y = y;
					boxes.push_back(p);
					goal_positions.push_back(p);
					board[x][y] = GOAL;
					break;
				case JENS_ONGOAL:
					jens.x = x;
					jens.y = y;
					p.x = x;
					p.y = y;
					goal_positions.push_back(p);
					board[x][y] = GOAL;
					break;
				case GOAL:
					p.x = x;
					p.y = y;
					goal_positions.push_back(p);
					board[x][y] = GOAL;
					break;
				default:
					board[x][y] = * iterator;
			}
			x++;
		}
		iterator++;
	}
	
	return new Node(jens, jens, &boxes, board);
}

/**
 * Return true if all boxes are on goal positions else false.
 */
bool solutionCheck(){
	for(unsigned int i =0; i<boxes.size(); i++){
		for(unsigned int j=0; j<goal_positions.size(); j++){
			if(boxes[i].x != goal_positions[j].x){
				return false;
			}
			if(boxes[i].y != goal_positions[j].y){
				return false;
			}
		}
	}
	return true;
}

/**
 * Solver
 */
string solve(Node * root)
{
	stack<Node> stacken;
//	stacken.push_back(&root);

	while(stacken.empty() && !solutionCheck())
	{
		
	}
}

/**
 * Main
 */
int main(int argc, char ** argv)
{
	// Command-line argument handling
//*  // Set or remove / at the beginning of this line to uncomment or comment following 18 lines
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
	boost::asio::ip::tcp::socket * socket = open(lHost, lPort);

	// välj board lBoard och läs in från server
	string boardStr(read(*socket, lBoard));
	cout << "Utskrit fra serv" << endl << boardStr;

	//***** HERE IS ACTION *****
	readBoard(boardStr);
	// XXX: Is this board solvable?
	//string test = "#############\n#############\n#####  ######\n#####     ###\n#####    ####\n###### #  ###\n###### #    #\n#     $**** #\n# $#$ $ ... #\n#       #@. #\n##########  #\n#############";

	//cout << test<<endl;
	//readBoard(test);
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
