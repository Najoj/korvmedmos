#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include <boost/unordered_set.hpp>

//Custom includes
#include "client.hpp"
#include "node.hpp"


#include "rules.hpp"

using namespace std;

Rules *rules;
deque<Node> stack;
/**
* Prints the board based on given board and node.
*/
/*void printBoard(Board & board, Node * node)
{
	bool found = false;
	cout << endl << "JENS position: x" << node->getCurrent_position().x << " Y " << node->getCurrent_position().y << endl;
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
}*/


/**
* Return true if all boxes are on goal positions else false.
*/
/*bool solutionCheck(Board & board, Node * node)
{
	for(int i =0; i<node->len; i++)
	{
		if (board.get(node->boxes_positions[i]) != GOAL) {
			return false;
		}
	}
	return true;
}*/

//typedef boost::unordered_set<Node> NodeSet;

/*bool been_in_node(NodeSet & nodeset, Node * node)
{
	NodeSet::iterator iterator = nodeset.find(*node);
	if (iterator != nodeset.end())
		return true;
	else
		return false;
}*/
Position getXYDir(int dir){
	Position ret(0,0);
	if(dir == UP)
		ret.y = -1;
	else if(dir == RIGHT)
		ret.x = 1;
	else if(dir == DOWN)
		ret.y = 1;
	else // dir == LEFT
		ret.x = -1;

	return ret;
}
void process(Node *n){


	int best_cost = FAIL;
	int best_dir = FAIL;
	//Kötta igenom alla direction
	for(unsigned int i = 0; i < 4; i++){
		if( rules->enforce(i, n) != FAIL){
			//Fick en bra väg att gå
			int temp = rules->heuristics(i,n);

			//Kollar om den är bäst
			if(temp < best_cost){
				best_cost = temp;
				best_dir = i;
			}
		}
	}

	if(best_dir == FAIL){
		//Poppa nått.
		stack.pop_front();
		return;
	}


	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));

	Node *temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir));
	stack.push_front( *temp );

}
/**
* Main
*/
int main(int argc, char ** argv)
{
	// Command-line argument handling
	//*  // Set or remove / at the beginning of this line to uncomment or comment following 18 lines
	std::string lHost,lPort,lBoard;

	bool PRINT = false;
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
	else if (argc==3)
	{
		lHost = std::string("cvap103.nada.kth.se");
		lPort = std::string("5555");
		lBoard = std::string(argv[1]);
		PRINT = (bool) argv[2];
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
	//Node rootNode = readBoard(boardStr, board);
	cout << boardStr;

	rules = new Rules(boardStr);

	//NodeSet nodeset;
	//nodeset.insert(rootNode);
	int iterations = 0;


	//Push root node onto stack


	while(!stack.empty())
	{
		process(&stack.front());
		cout << "Iteration " << iterations << endl;
		if(iterations == 37){
			int apa = 1;
		}
		iterations++;
		if(PRINT){
			//	printBoard(board, child);
			//sleep(0.1);
				cin.get();
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
		//solution += moves_real[stack.back().LAST_DIR] + " ";
		stack.pop_back();
	}

	cout << "Solution:\t" << solution << endl;
	cout << "Iterations:\t" << iterations << endl;

	// skicka in lösning och skriv ut svar
	cout << "Server answer:\t";
	send(*socket, solution);
	return 0;
}
