#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <queue>
#include <boost/unordered_set.hpp>
//Custom includes
#include "client.hpp"
#include "node.hpp"
//#include "rules.hpp"
#include "heuristics.hpp"
#include "common.hpp"

using namespace std;

Heuristics *rules;

// Priority queue of node pointers with an appropriate comparer
struct compare_node
{
	bool operator()(Node * node1, Node * node2) const
	{
		return node1->getPathCost()+node1->getGoalCost() > node2->getPathCost()+node2->getGoalCost();
	}
};
priority_queue<Node*, vector<Node*>, compare_node> pqueue;

Node * last_node;
Position getXYDir(int dir, Position ret = Position(0,0) ){
	if(dir == UP)
		ret.y += -1;
	else if(dir == RIGHT)
		ret.x += 1;
	else if(dir == DOWN)
		ret.y += 1;
	else // dir == LEFT
		ret.x += -1;

	return ret;
}

/**
 * Processes nodes, return true if solution was found else otherwise.
 */
bool process(Node *n)
{
	unsigned int best_cost = -1;		// BIG value.
	unsigned int way_to_walk;
	int best_dir = -1;

	//Set node in process
	rules->set_node(n);
	//Add the boxes to the board (from node in process)
	rules->addBoxes();

	// Go through all the four possible directions.
	for(unsigned int i = 0; i < 4; i++) {
		int enforce_return = rules->enforce(i);
		if( enforce_return != FAIL) {
			// Recives a way to walk.
			way_to_walk = rules->heuristics(i);

			// Find a solution with the best cost
			if (way_to_walk < best_cost) {
				best_cost = way_to_walk;
				best_dir = i;
			}
		}
	}

	rules->removeBoxes();

	// If we didnt find any good direction
	if(best_dir == -1) {
		pqueue.pop();
		return false;
	}

	// Move jens
	Position jens = n->getCurrent_position();
	jens.addPosition(getXYDir(best_dir));

	// Next state
	Node * next = new Node(jens, n, n->getBoxes(), n->getLen(), getXYDir(best_dir), best_dir);

	rules->addBoxes();
	next->setGoalCost(rules->total_goal_distance(next));

	//Marks this node, or state as visited.
	rules->markAsVisited(next);
	//Clears the board from boxes
	rules->removeBoxes();	
	
	if(rules->solutionCheck(next))
	{
		last_node = next;
		cout << "DONE!" << endl;
		return true;
	}

	pqueue.push(next);
	return false;
}

/**
 * Main
 */
int main(int argc, char ** argv)
{
	// Command-line argument handling
	string host, port, board_nr;
	boost::asio::ip::tcp::socket * socket = NULL;
	string board_str;
	bool server = false;

	if (argc > 1) // Use server
	{
		switch (argc)
		{
			case 2:
				host = string("cvap103.nada.kth.se");
				port = string("5555");
				board_nr = string(argv[1]);
				break;
			case 3:
				host = string("cvap103.nada.kth.se");
				port = string("5555");
				board_nr = string(argv[1]);
				break;
			case 4:
				host = string(argv[1]);
				port = string(argv[2]);
				board_nr = string(argv[3]);
				break;
		}
		// Open a socket with a connection to the server.
		socket = open(host, port);

		// Reads board_str from the server.
		board_str = string(read(*socket, board_nr));
		cout << "Reading from server" << endl;
		server = true;
	}
	else // Read from stdin
	{
		string fbuf;
		while(cin) {
			getline(cin, fbuf);
			board_str += fbuf + '\n';
		}
		cout << "Reading from stdin" << endl;
	}
	
	cout << board_str << endl; // Print board as read
	rules = new Heuristics(board_str); // Create the rules and parse indata

	// Make the root node, this will be pushed onto pqueue
	Node rootNode = rules->getRootNode();
	rules->set_node(&rootNode);
	rules->addBoxes();
	rules->printBoard(&rootNode);
	rules->markAsVisited(&rootNode);
	pqueue.push(&rootNode);
	
	// Main loop
	int iterations = 0;	
	while(!pqueue.empty())
	{
		// If solution was found break
		if (process( pqueue.top())){
			break;
		}
		// If too many iterations give up so the program doesn't eat up the entire RAM
		if(iterations > 10000000){
			cerr << "FAIL: Too many iterations, exiting..." << endl;
			rules->printBoard(pqueue.top());
			exit(0);
		}
		//rules->printBoard(&pqueue.front());
		iterations++;
	}
	cout << "Iterations:\t" << iterations << endl;
	if(pqueue.empty()) // This should not happen, if it happens there was a bug in the code
	{
		cerr << "FAIL: pqueue turned out to be empty. Not good."<< endl;
		exit(1);
	}
	
	// Extract solution by backtracking
	string solution;
	Node * tmp = last_node;
	do{
		solution += moves_real[tmp->LAST_DIR] +  " ";
		tmp = tmp->getParent();
	}
	while(!(*tmp == rootNode));

    // Reverse the string into correct ordet.
    string::iterator pos;
    string rev_solution;
    for (pos = solution.end(); pos != solution.begin()-1; pos--) {
        rev_solution += *pos;
    }
	cout << "Solution:\t" << rev_solution << endl;

	if (server)
	{
		// Send a solution and prints
		cout << "Server answer:\t";

		//Substring, thanks Javier!
		send(*socket, rev_solution.substr(1,rev_solution.length()));
	}
	
	return 0;
}
