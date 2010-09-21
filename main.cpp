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
int **board;        // Used for representing the entire board.
int width, height;  // Width and height of the board.

//Ze boxes
 vector<Position> boxes;
 vector<Position> goal_positions;

Node * root;        // Root node.
Node * getChildState(Node *n);  // Returns null if no child is avaible.

/**
 * Methods
 */
void readBoard(std::string);    // Reads the board into matrix.

/**
 * Fecthes child of root n.
 */
Node * getChildState(Node *n){
	//n->getBoxes();
	return NULL;
}

/* XXX: Removeable? Does not seem to be doing anything at all.
void readBoard(){

}
*/
/**
 * Prints the board based on the board global variable.
 */
void printBoard()
{
	//cout << "H: "<< height << " W:" << width<<endl;
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
    // Creates an iterator.
	string::iterator iterator;
	iterator = boardIn.begin();

	//Get the lenght of the board. Which is the position of first '\n'.
	width = boardIn.find("\n");


	// Height is then the total length of the string, divide with the height.
	height = boardIn.length() / width;
	cout << "H: "<< height << " W:" << width<<endl;


	//Allocate memory for the board
	board = new int*[height];

    // Koskenkorva.
	int x = 0, y = 0;
	
	int box = 0;    // Counting boxes.
	Position jens;  // Jens is the man, this is his position. Will be in root.
	
	//Allocate memory for the first column.
	board[x] = new int[width];
	


	while(iterator != boardIn.end())
	{
		if(*iterator == '\n')
		{

			x++;
			y = 0;
			//New full column. Matrix hack.
			board[x] = new int[width];

		} else {
			//Assign the value from the board.
    	/*	if(*iterator == BOX || *iterator == BOX_ONGOAL ) {
    		    // My name is Boxxy. Counts boxes so that we can allocate them later.
		       box++;
    		} else if(*iterator == JENS || *iterator == JENS_ONGOAL ) {
    		    // Got Jens?
    		    jens.x = x;
    		    jens.y = y;
//	    	    root->p_current_position = jens;  // Saving position in root node.
    		}*/

			if(*iterator == BOX  || *iterator == JENS ){
				if(*iterator == BOX){

					/**
					 * Classic JAKEHAX
					 */
					Position p;
					p.x = y;
					p.y = x;
					//cout << "X: e " << x << "Y: e " << y << endl;
					boxes.push_back(p);
				}
				if(*iterator == JENS ){
					jens.x = y;
					jens.y = x;
				}
				board[x][y] = FLOOR;
			}else if(*iterator == BOX_ONGOAL|| *iterator == JENS_ONGOAL){
				if(*iterator == BOX_ONGOAL){
					Position p;
					p.x = y;
					p.y = x;
					boxes.push_back(p);
					goal_positions.push_back(p);
				}
				if(*iterator == JENS_ONGOAL){
					jens.x = y;
					jens.y = x;
					/**
					 * Classic JAKEHAX
					 */
					Position p;
					p.x = y;
					p.y = x;
					goal_positions.push_back(p);
				}
				board[x][y] = GOAL;
			}else if(*iterator == GOAL){
				/**
				* Classic JAKEHAX
				*/
				Position p;
				p.x = y;
				p.y = x;
				goal_positions.push_back(p);
			}

			else{
				board[x][y] = * iterator;
			}
    		y++;


		}		
		iterator++;
	}
	
	//MAke root node.
	Node *root = new Node(boxes.size(),jens,jens, &boxes);

/*

	for(unsigned int i = 0; i<boxes.size();i++){
		cout <<"X aer: " << boxes[i].x << " Y e " << boxes[i].y << endl;
	}

	cout << "JENS : " << jens.x << " " << jens.y << endl;
	*/
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


	// välj board lBoard och läs in från server
//	string boardStr ( read(*socket, lBoard));
//	boardStr.
	//read(NULL,NULL);
	
//	cout << "Utskrit fra serv" << endl << boardStr;


	//***** HERE IS ACTION *****
	//readBoard(boardStr);
	// XXX: Is this board solvable?
	string test = "#############\n#############\n#####  ######\n#####     ###\n#####    ####\n###### #  ###\n###### #    #\n#     $**** #\n# $#$ $ ... #\n#       #@. #\n##########  #\n#############";

	cout << test<<endl;
	readBoard(test);
    // Mostly for debugging purposes.
	//printBoard();
	
/*
    Todo here:
     * Parse board into a tree graph.
     * Search in tree.
     * Make the solution
     - Johan
*/

	while(!solutionCheck()){

	}


	std::string solution = ("U R R D U U L D L L U L L D R R R R L D D R U R U D L L U R");
	// skicka in lösning och skriv ut svar
	//send(*socket, solution);
	return 0;
}
