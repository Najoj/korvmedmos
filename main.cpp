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

bool process(Node *n)
{
        unsigned int best_cost = -1;        // BIG value.
        unsigned int way_to_walk;
        int best_dir;
        int best_dirs[] = {-1,-1,-1,-1};                                   // RANDOM WALK
        int mod = 0;
        // Go through all the four possible directions.
        for(unsigned int i = 0; i < 4; i++){
        		int enforce_return = rules->enforce(i, n); 
                if( enforce_return != FAIL){
                        cout << "Fann en bra väg! " << moves_real[i] << endl;

                        // Recives a way to walk.
                        way_to_walk = rules->heuristics(i,n,enforce_return);
                        cout << "cost: " << way_to_walk << endl;
                        // Checks if the best
                        if(way_to_walk == best_cost){
//                              best_dir = i;

                                best_dirs[mod] = i;                                             // RANDOM WALK
                                mod++;                                                          // RANDOM WALK
                        //      cout << "Updatera bestidr " << moves_real[best_dir] << endl;
                        } else if (way_to_walk < best_cost) {
                                best_cost = way_to_walk;
                                best_dirs[0] = i;                                               // RANDOM WALK
                                mod = 1;
                        }
                }
        }

    if(mod > 0)                                                                 // RANDOM WALK
    {
            srand(time(0));
//            best_dir = best_dirs[rand() % mod];
            best_dir = best_dirs[0];
        }
        else
        {
                // Poped.
                cout << "POPPADE DIG :D" << endl;
                stack.pop_front();
                return false;
        }

        Position p = n->getCurrent_position();

        p.addPosition(getXYDir(best_dir));

        Position boxmov = p;
        boxmov.addPosition(getXYDir(best_dir));
        Node *temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);
//      cout <<  "gjort en barn med dir: " << moves_real[best_dir] << endl;
        rules->markAsVisited(temp);

        rules->printBoard(temp);

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
	std::string lHost,lPort,lBoard;

	bool PRINT = true;
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
		if (process(&stack.front())) break;
		cout << "Iteration " << iterations << endl;

		if(iterations == 59){
			//exit(0);
		}
		iterations++;
		if(PRINT)
		{
			rules->printBoard(&stack.front());
			//sleep(0.1);
				cin.get();
		}

	}
	
	if(stack.empty())
	{
		cout << "FAIL: Stack turned out to be empty. Not good."<< endl;
		exit(1);
	}

	string solution;
	// frontens LAST_DIR är odef 
//	stack.pop_front(); 
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
