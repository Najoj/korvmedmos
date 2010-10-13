#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include <boost/unordered_set.hpp>
#include <cstdlib>	// Used for random.
#include <ctime>	// Used for seed.

//Custom includes
#include "client.hpp"
#include "node.hpp"
#include "rules.hpp"
#include "common.hpp"

using namespace std;

Rules *rules;
deque<Node> stack;

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
		// Go through all the four possible directions.
		for(unsigned int i = 0; i < 4; i++){
				int enforce_return = rules->enforce(i, n); 
				if( enforce_return != FAIL){
//						cout << "Fann en bra väg! " << moves_real[i] << endl;

						// Recives a way to walk.
						way_to_walk = rules->heuristics(i,n,enforce_return);
//						cout << "cost for " << moves_real[i] << ": " << way_to_walk << endl;
						// Checks if the best
						if(way_to_walk == best_cost){
//							  best_dir = i;

								best_dirs[mod] = i;											 // RANDOM WALK
								mod++;														  // RANDOM WALK
						//	  cout << "Updatera bestidr " << moves_real[best_dir] << endl;
						} else if (way_to_walk < best_cost) {
								best_cost = way_to_walk;
								best_dirs[0] = i;											   // RANDOM WALK
								mod = 1;
						}
				}
		}

	if(mod > 0)																 // RANDOM WALK
	{
//			srand(time(0));
//			best_dir = best_dirs[rand() % mod];
			best_dir = best_dirs[0];
		}
		else
		{
				// Poped.
//				cout << "POPPADE DIG :D" << endl;
				stack.pop_front();
				return false;
		}

		Position p = n->getCurrent_position();

		p.addPosition(getXYDir(best_dir));

		Position boxmov = p;
		boxmov.addPosition(getXYDir(best_dir));
		Node *temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);
//	  cout <<  "gjort en barn med dir: " << moves_real[best_dir] << endl;
		rules->markAsVisited(temp);

//		rules->printBoard(temp);

		if(rules->solutionCheck(temp)){
				cout << "DONE!" << endl;
				return true;
		}
		stack.push_front( *temp );
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
	rules = new Rules(board_str); // Create the rules and parse indata

	// Make the root node, this will be pushed onto stack later on!
	Node rootNode = rules->getRootNode();
	rules->printBoard(&rootNode);
	rules->markAsVisited(&rootNode);
	stack.push_front(rootNode);

	int iterations = 0;	
	srand(time(0)); // Seed for the random.

	while(!stack.empty())
	{
		if (process(&stack.front()))
			break;
//		cout << "Iteration " << iterations << endl;
		if(iterations > 20000000){
			cerr << "FAIL: Too many iterations, exiting..." << endl;
			rules->printBoard(&stack.front());
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
	while(!stack.empty())
	{
		solution += moves_real[stack.back().LAST_DIR] + " ";
		stack.pop_back();
	}

	cout << "Solution:\t" << solution << endl;

	if (server)
	{
		// Send a solution and prints
		cout << "Server answer:\t";
		send(*socket, solution);
	}
	
	return 0;
}
