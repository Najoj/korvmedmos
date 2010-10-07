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
void debug_print(std::string text)
{
	if (DEBUG) std::cout << text << std::endl;
}
void process(Node *n){
	int best_cost = BIG_VALUE;        // BIG value.
	int new_cost;
	int best_dir;
	int best_dirs[] = {-1,-1,-1,-1};                                   // RANDOM WALK
	int mod = 0;
	// Go through all the four possible directions.
	for(unsigned int i = 0; i < 4; i++){
		if( rules->enforce(i, n) != FAIL ){
			cout << "Should go to: " << moves_real[i] << endl;
	
			// Recives a way to walk.
			new_cost = rules->heuristics(i,n);
			cout << "New cost: " << new_cost << endl;
//			new_cost = 1;
			// Checks if the best
			if(new_cost == best_cost){
	//			best_dir = i;
				best_dirs[mod] = i;                                             // RANDOM WALK
				mod++;                                                          // RANDOM WALK
			//	cout << "Updatera bestidr " << moves_real[best_dir] << endl;
			} else if ( 0 <= new_cost && new_cost < best_cost) {
				best_cost = new_cost;
				best_dirs[0] = i;                                               // RANDOM WALK
				mod = 1;
			}
		}
	}
    if(mod > 0)                                                                 // RANDOM WALK
    {
	    best_dir = best_dirs[rand() % mod];
//	    cout << "Best dir: " << best_dir << endl;
	}
	else
	{
		// Poped.
		debug_print("Poped something.");
		stack.pop_front();
		return;
	}

	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));

	Position boxmov = p;
	boxmov.addPosition(getXYDir(best_dir));
	Node *temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir));
//	cout <<  "gjort en barn med dir: " << moves_real[best_dir] << endl;
	rules->markAsVisited(temp);

	rules->printBoard(temp);

	if(rules->solutionCheck(temp)){
		cout << "Done!" << endl;
		exit(0);
	}
	stack.push_front( *temp );

}
/**
 * Main
 */
int main(int argc, char ** argv)
{
	// Command-line argument handling
	std::string lHost,lPort,lBoard;

	bool PRINT = false;
/*
	if (argc==2)
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
	else if(argc==4)
	{
		lHost = std::string(argv[1]);
		lPort = std::string(argv[2]);
		lBoard = std::string(argv[3]);
	}
	else
	{
		std::cerr << "Usage: main (<host> <port>) <board2Solve>" << std::endl;
		return 1;
	}
*/	
	// Open a socket with a connection to the server.
	//boost::asio::ip::tcp::socket * socket = open(lHost, lPort);

	// Reads lBoard from the server.
	//string boardStr(read(*socket, lBoard));



//	cout << boardStr;

	string boardStr;
	string fbuf;
	
	while(cin) {
	    getline(cin, fbuf);
		boardStr += fbuf +"\n";
	};

	cout << "Read from stdin:\n" <<  boardStr << endl;

	// Create the rules and parse indata
	rules = new Rules(boardStr);

	// Make the root node, this will be pushed onto stack later on!
	Node rootNode = rules->getRootNode();


	rules->printBoard(&rootNode);

	rules->markAsVisited(&rootNode);

	stack.push_front(rootNode);

	//NodeSet nodeset;
	//nodeset.insert(rootNode);
	int iterations = 0;
	
	// Seed for the random.
	srand(time(0));

	// Push root node onto stack.


	while(!stack.empty())
	{
		process(&stack.front());
		cout << "Iteration " << iterations << endl;

		iterations++;
		if(PRINT)
		{
			//	printBoard(board, child);
			//sleep(0.1);
				cin.get();
		}

	}
	cout << "Done!" << endl;
	
	if(stack.empty())
	{
		cout << "Stack turned out to be empty. Not good."<< endl;
		exit(1);
	}

	string solution;
	// First node has no LAST_SET, may cause weird errors.
	stack.pop_front();
	while(!stack.empty())
	{
		solution += moves_real[stack.back().LAST_DIR] + " ";
		stack.pop_back();
	}

	cout << "Solution:\t" << solution << endl;
	cout << "Iterations:\t" << iterations << endl;

	// Send a solution and prints
	cout << "Server answer:\t";
	//send(*socket, solution);
	return 0;
}
