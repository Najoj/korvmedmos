#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include <boost/unordered_set.hpp>

//Custom includes
#include "client.hpp"
#include "node.hpp"
#include "Board.hpp"
using namespace std;

/**
* Prints the board based on given board and node.
*/
void printBoard(Board & board, Node * node)
{
	bool found = false;
	for(int j = 0; j < board.height; j++)
	{
		for(int i = 0; i < board.width; i++)
		{
			if(node->getCurrent_position().x == i && node->getCurrent_position().y == j)
			{
				cout << JENS;
				continue;
			}
			found = false;
			for(int k = 0; k < node->len; k++)
			{
				if(node->boxes_positions[k].x == i && node->boxes_positions[k].y == j)
				{
					if (board.get(node->boxes_positions[k]) == GOAL)
						cout << BOX_ONGOAL;
					else
						cout << BOX;
					
					found = true;
					break;
				}
			}
			if(!found)
			{
				cout << (unsigned char) board.get(i,j) << "";
			}
		}
		cout << endl;
	}
}

/**
* Reads the board into a int matrix called board (global var)
* @param string The String representing the board.
*/
Node readBoard(std::string boardIn, Board & board)
{
	// Creates an iterator.
	string::iterator iterator;
	iterator = boardIn.begin();
	vector<Position> boxes;

	//Get the lenght of the board. Which is the position of first '\n'.
	int width = boardIn.find("\n");
	// Height is then the total length of the string, divide with the height.
	int height = boardIn.length() / width;
	cout << "Height:\t" << height << endl << "Width:\t" << width << endl;

	// Koskenkorva.
	int x = 0, y = 0;

	Position jens;  // Jens is the man, this is his position. Will be in root.

	//Allocate memory for matrix, an iterates.
	for(board = Board(width, height) ; iterator != boardIn.end(); iterator++)
	{
		if(*iterator == '\n')
		{
			// if newline add y (column)
			y++;
			x = 0;
		}
		else
		{
			Position p(x,y);
			switch (*iterator) {
				case BOX:
					boxes.push_back(p);
					board.set_floor(p);
					break;
				case JENS:
					jens = p;
					board.set_floor(p);
					break;
				case BOX_ONGOAL:
					boxes.push_back(p);
					board.add_goal(p);
					break;
				case JENS_ONGOAL:
					jens = p;
					board.add_goal(p);
					break;
				default:
					board.get(p) = *iterator;
			}
			x++;
		}
	}
	return Node(jens, jens, &boxes, &board);
}

/**
* Return true if all boxes are on goal positions else false.
*/
bool solutionCheck(Board & board, Node * node)
{
	for(int i =0; i<node->len; i++)
	{
		if (board.get(node->boxes_positions[i]) != GOAL) {
			return false;
		}
	}
	return true;
}

typedef boost::unordered_set<Node> NodeSet;

bool been_in_node(NodeSet & nodeset, Node * node)
{
	NodeSet::iterator iterator = nodeset.find(*node);
	if (iterator != nodeset.end())
		return true;
	else
		return false;
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

	// Open a socket with a connection to the server.
	boost::asio::ip::tcp::socket * socket = open(lHost, lPort);

	// Reads lBoard from the server.
	string boardStr(read(*socket, lBoard));

	//***** HERE IS ACTION *****
	Board board;
	Node rootNode = readBoard(boardStr, board);
	cout << boardStr;

	NodeSet nodeset;
	nodeset.insert(rootNode);
	int iterations = 0;
	deque<Node> stack;

	//Push root node onto stack
	stack.push_front(rootNode);

	while(!stack.empty() && !solutionCheck(board, &stack.front()))
	{
		iterations++;
		Node *child;
		if((child = stack.front().getChild())  == NULL)
		{
			stack.pop_front();
		}
		else if (!been_in_node(nodeset, child))
		{
			//check if we already visited child.
			nodeset.insert(*child);
			stack.push_front(*child);
			//printBoard(board, child);
			//sleep(0.1);
			//cin.get();
		}
	}

	if(stack.empty())
	{
		cout << "Stack turned out to be empty. Not good."<< endl;
		exit(1);
	}

	string solution;
	stack.pop_front(); // First node has no LAST_SET, may cause weird error
	while(!stack.empty())
	{
		solution += moves_real[stack.back().LAST_DIR] + " ";
		stack.pop_back();
	}

	cout << "Solution:\t" << solution << endl;
	cout << "Iterations:\t" << iterations << endl;

	// skicka in lösning och skriv ut svar
	cout << "Server answer:\t";
	send(*socket, solution);
	return 0;
}
