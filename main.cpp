#include <iostream>
#include <boost/asio.hpp>
#include <boost/multi_array.hpp>
#include <vector>
#include <deque>
//#include <boost/detail/default_hash.hpp>
#include <boost/bloom_filter.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/functional/hash.hpp>

//Custom includes
#include "client.hpp"
#include "node.hpp"

using namespace std;
using boost::bloom_filter;

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
Node readBoard(std::string);    // Reads the board into matrix.

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
 * Prints the board based on the board global variable.
 */
void printBoard(Node *node)
{
bool found = false;
	for(int j = 0; j < height; j++)
	{
		for(int i = 0; i < width; i++)
		{
			if(node->getCurrent_position().x == i && node->getCurrent_position().y == j){
				cout << JENS;
				continue;
			}
			found = false;
			for(unsigned int k = 0; k < boxes.size(); k++){
				if(node->boxes_positions[k].x == i && node->boxes_positions[k].y == j){
					cout << BOX;
					found = true;
					break;
				}
			}
			if(!found){
				cout << (unsigned char) board[i][j] << "";
			}
		}
		cout << endl;
	}
}

/**
 * Reads the board into a int matrix called board (global var)
 * @param string The String representing the board.
 */
Node readBoard(std::string boardIn)
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
	
	return Node(jens, jens, &boxes, board);
}

/**
 * Return true if all boxes are on goal positions else false.
 */
bool solutionCheck(Node * node){
	for(unsigned int i =0; i<boxes.size(); i++){
		for(unsigned int j=0; j<boxes.size(); j++){
			if(node->boxes_positions[i].x == goal_positions[j].x && node->boxes_positions[i].y == goal_positions[j].y){
				break;
			}
			//Found one box that is not on goal position.
			if(j == goal_positions.size() -1 ){
				return false;
			}
		}
	}
	cout <<  "FOUND SOLTUIN!!!!!!!!!!!!" << endl;
	return true;
}

/**
 * Solver
 */
string solve(Node * root)
{

	return NULL;
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

	//***** HERE IS ACTION *****
	Node rootNode = readBoard(boardStr);

	bloom_filter<Node> visited_boxes(90000048);

	visited_boxes.insert(rootNode);
//	visited_jens.insert(rootNode.getCurrent_position().x * rootNode.getCurrent_position().y );


	int iterations = 0;

	deque<Node> stack;
	//stacken.push_back(&root);

	//Push root node onto stack
	stack.push_front(rootNode);

	while(!stack.empty() && !solutionCheck(&stack.front()))
	{

		iterations++;
		Node *child;
	//	cout << "Position e just nu : " << stack.front().getCurrent_position().x << " "<< stack.front().getCurrent_position().x<<endl;
		if((child = stack.front().getChild())  == NULL){

			cout << "Nu poppar vi :D! " << stack.front().getCurrent_position().x << " " << stack.front().getCurrent_position().y << endl;
			stack.pop_front();
			//exit(1337);
		}else{

			//if(visited_jens.contains(child->getCurrent_position().x*child->getCurrent_position().y)){
				//				cout << "JEns samma";
					//		}
			//check if we already visited child.
			if( !visited_boxes.contains(*child)){
					/*&& visited_jens.contains(child->getCurrent_position().x*child->getCurrent_position().y)))*/
/*
				if(!visited_boxes.contains(child->sumBoxes())){
					cout << "Boxes inte sammas!";
				}
				*/

				visited_boxes.insert(*child);
			//	visited_jens.insert(child->getCurrent_position().x*child->getCurrent_position().y);
				child->print();
				stack.push_front(*child);
			}else{
				cout <<"Redan besökt" << child->getCurrent_position().x<< " " << child->getCurrent_position().y <<  endl;
				//child->print();
			}
		}
	}

	//Goal node hackzz
	//stack.pop_back();
	string solution;
	while(!stack.empty()){
			//cout << moves_real[stack.top().LAST_DIR] << endl;
		printBoard(&stack.back());
		solution += moves_real[stack.back().LAST_DIR] + " ";
		stack.pop_back();
		//cin.get();
	}
	cout << solution << endl;
	cout << iterations << endl;
	cout << "Löst probbet?" << endl;
	//cout << test<<endl;
	//readBoard(test);
    // Mostly for debugging purposes.
	printBoard();

	// skicka in lösning och skriv ut svar
	send(*socket, solution);
	return 0;
}
