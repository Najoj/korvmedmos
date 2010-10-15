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
#include "common.hpp"

using namespace std;

Heuristics *rules;

priority_queue<Node> stack;

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
//			cout << "Fann en bra väg! " << moves_real[i] << endl;


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
		stack.pop();
		return false;
	}


	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));

	Node *temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);

	//cout << "Skapa barn med parent: " << n << " jp " <<(int) n->getCurrent_position().x << ","<< (int)n->getCurrent_position().y<< endl;
	//cout << "(tmp): " << temp<< " jp " << (int)temp->getCurrent_position().x << ","<<(int)temp->getCurrent_position().y<< endl;
//	  cout <<  "gjort en barn med dir: " << moves_real[best_dir] << endl;

	// Heruistics for A*

	//cout << "====================================="<<endl;
	//cout << "JENS POS "<<(int)temp->getCurrent_position().x << " y: " << (int)temp->getCurrent_position().y << endl;
	rules->set_node(temp);
	rules->addBoxes();
	//cout << "Board" << endl;
	//rules->printBoard(temp);
	temp->setGoalCost(rules->total_goal_distance(temp));
	//cout << "Uber haxx " << temp->getGoalCost() << endl;
	//Marks this node, or state as visited.
	rules->markAsVisited(temp);

	//Clears the board from boxes
	rules->removeBoxes();
	//cout << "====================================="<<endl<<endl;




	if(rules->solutionCheck(temp)){

			last_node = temp;
			cout << "DONE!" << endl;
			return true;
	}

	stack.push( *temp );
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
	rules = new Heuristics(board_str); // Create the rules and parse indata

	// Make the root node, this will be pushed onto stack later on!
	Node rootNode = rules->getRootNode();
	rules->set_node(&rootNode);
	rules->addBoxes();
	rules->printBoard(&rootNode);
	rules->markAsVisited(&rootNode);
	stack.push(rootNode);


	int iterations = 0;	
	srand(time(0)); // Seed for the random.

	while(!stack.empty())
	{

		Node * node = new Node(stack.top());
		//FEWL HACKZZ
		if (process( node ) ){
				break;
		}
//		cout << "Iteration " << iterations << endl;
		if(iterations > 20000000){
			cerr << "FAIL: Too many iterations, exiting..." << endl;
			rules->printBoard(const_cast<Node*>( &stack.top() ));
			exit(0);
		}
		//rules->printBoard(&stack.front());
		iterations++;
	}
	cout << "Iterations:\t" << iterations << endl;
	if(stack.empty())
	{
		cerr << "FAIL: Stack turned out to be empty. Not good."<< endl;
		exit(1);
	}
	
	string solution;
	bool done = false;
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
