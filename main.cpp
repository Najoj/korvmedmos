#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include <queue>
#include <boost/unordered_set.hpp>
#include <cstdlib>	// Used for random.
#include <ctime>	// Used for seed.

//Custom includes
#include "client.hpp"
#include "node.hpp"
//#include "rules.hpp"
#include "heuristics.hpp"
#include "back/back_heuristics.hpp"
#include "common.hpp"

using namespace std;

BackHeuristics *rules;

BackHeuristics *back_rules;

/**
 * Varför blev allt bättre när jag bytte till Nod*?
 */
priority_queue<Node*> stack;

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
int revereseDir(int push_box_dir){
if(push_box_dir == RIGHT)
	return LEFT;
else if(push_box_dir == LEFT)
	return RIGHT;
else if(push_box_dir == UP)
	return DOWN;
else if(push_box_dir == DOWN)
	return UP;
}
void debug_print(std::string text)
{
	if (DEBUG) std::cout << text << std::endl;
}

bool process(Node *n)
{
	unsigned int best_cost = -1;		// BIG value.
	unsigned int way_to_walk;
	int best_dir;
	int best_dirs[] = {-1,-1,-1,-1};								   // RANDOM WALK
	int mod = 0;

	//Set node in process
	rules->set_node(n);

	//Add the boxes to the board (from node in process)
	rules->addBoxes();

	// Go through all the four possible directions.
	for(unsigned int i = 0; i < 4; i++) {
		int enforce_return = rules->enforce(i);
		if( enforce_return != FAIL) {
		cout << "Fann en bra väg! " << moves_real[i] << endl;


			// Recives a way to walk.
			way_to_walk = rules->heuristics(i);


//				cout << "cost for " << moves_real[i] << ": " << way_to_walk << endl;
			// Checks if the best
			if(way_to_walk == best_cost){
//					best_dir = i;
					best_dirs[mod] = i;
					mod++;

			} else if (way_to_walk < best_cost) {
					best_cost = way_to_walk;
					best_dirs[0] = i;
					mod = 1;
			}
		}
	}

	rules->removeBoxes();

	//Chose what direction to walk
	if(mod > 0)
	{
//		srand(time(0));
//		best_dir = best_dirs[rand() % mod];
		best_dir = best_dirs[0];
	}
	//We didnt find any good direction
	else{
		cout << "Pooop" << endl;
		stack.pop();
		return false;
	}

	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));
	cout <<"kommer ga: " << moves_real[best_dir] << "dvs till " << (int) p.x << "," << (int)p.y << endl;






	//THIS USES BACK CONSTRUCTOR RIGHT NOW!!
	Node *temp = new Node(p, n->getCurrent_position(),n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);


	rules->set_node(temp);
	//rules->addBoxes();

	//rules->printBoard(temp);
//	temp->setGoalCost(rules->total_goal_distance(temp));
	temp->setGoalCost(1);
	//Marks this node, or state as visited.
	rules->markAsVisited(temp);

	//Clears the board from boxes
	//rules->removeBoxes();





	if(rules->solutionCheck(temp)){

			last_node = temp;
			cout << "DONE!" << endl;
			return true;
	}

	stack.push( temp );
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

		// Reads lBoard from the server.
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
	rules = new BackHeuristics(board_str); // Create the rules and parse indata
/*
	back_rules = new BackHeuristics(board_str);	//Creates backwards rules

	Node bRootNode = back_rules->getRootNode();

	back_rules->set_node(&bRootNode);
	back_rules->addBoxes();
	back_rules->printBoard(&bRootNode);
	back_rules->markAsVisited(&bRootNode);
	//exit(0);*/

	// Make the root node, this will be pushed onto stack later on!
	Node rootNode = rules->getRootNode();
	rules->set_node(&rootNode);
	rules->addBoxes();
	rules->printBoard(&rootNode);
	rules->markAsVisited(&rootNode);
	stack.push(&rootNode);



	int iterations = 0;	
	srand(time(0)); // Seed for the random.

	while(!stack.empty())
	{

		Node * node = stack.top();
		//FEWL HACKZZ
		if (process( node ) ){
				break;
		}
//		cout << "Iteration " << iterations << endl;
		if(iterations > 20000000){

			cerr << "FAIL: Too many iterations, exiting..." << endl;
			rules->printBoard(const_cast<Node*>( stack.top() ));
			exit(0);
		}
		if(iterations >= 9){

		exit(0);
		}
		cout << "========== N STATE=========" << endl;
		rules->set_node(stack.top());
		rules->addBoxes();
		rules->printBoard(stack.top());
		rules->removeBoxes();
		iterations++;
	}
	cout << "Iterations:\t" << iterations << endl;
	if(stack.empty())
	{
		cerr << "FAIL: Stack turned out to be empty. Not good."<< endl;
		exit(1);
	}
	
	string solution;

	//FEWL HACKZ
	//Node * temp = const_cast<Node*>( &stack.top() );
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
