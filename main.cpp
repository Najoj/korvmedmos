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

Heuristics * forward_rules;

BackHeuristics *back_rules;

Node * f_rootNode;
Node * b_rootNode;
bool search_back = false;

Position jens_start_back;
string board_str;

Node * back_last_node = NULL;
Node * forward_last_node = NULL;
/**
 * Varför blev allt bättre när jag bytte till Nod*?
 */

struct compare_node
{
	bool operator()(Node * node1, Node * node2)
	{
		return node1->getPathCost()+node1->getGoalCost() < node2->getPathCost()+node2->getGoalCost();
	}
};
priority_queue<Node*, vector<Node*>, compare_node> forward_stack;
priority_queue<Node*, vector<Node*>, compare_node> back_stack;


Position getXYDir(int dir){
	Position ret;
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
return NO_DIR;
}
void debug_print(std::string text)
{
	if (DEBUG) std::cout << text << std::endl;
}
void printBoard(Node * n ){

	forward_rules->set_node(n);
	forward_rules->addBoxes();
	forward_rules->printBoard(n);
	forward_rules->removeBoxes();

}
int forward_process(Node *n)
{
	unsigned int best_cost = -1;		// BIG value.
	unsigned int way_to_walk;
	int best_dir;
	int best_dirs[] = {-1,-1,-1,-1};								   // RANDOM WALK
	int mod = 0;

	//Set node in process
	forward_rules->set_node(n);

	//Add the boxes to the board (from node in process)
	forward_rules->addBoxes();

	// Go through all the four possible directions.
	for(unsigned int i = 0; i < 4; i++) {
		int enforce_return = forward_rules->enforce(i);
		if( enforce_return != FAIL) {
		//cout << "Fann en bra väg! " << moves_real[i] << endl;


			// Recives a way to walk.
			way_to_walk = forward_rules->heuristics(i);


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

	forward_rules->removeBoxes();

	//Chose what direction to walk
	if(mod > 0)
	{
//		srand(time(0));
//		best_dir = best_dirs[rand() % mod];
		best_dir = best_dirs[0];
	}
	//We didnt find any good direction
	else{
		cout << "Main Pooop FORWARD" << endl;
		forward_stack.pop();
		return OK;
	}

	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));
	//cout <<"kommer ga: " << moves_real[best_dir] << "dvs till " << (int) p.x << "," << (int)p.y << endl;



		Node * temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);


			forward_rules->set_node(temp);
			forward_rules->addBoxes();

			//rules->printBoard(temp);
			temp->setGoalCost(forward_rules->total_goal_distance(temp));
		//	temp->setGoalCost(0);
			//Marks this node, or state as visited.
			forward_rules->markAsVisited(temp);

			//Clears the board from boxes
			forward_rules->removeBoxes();

			//Check if we want to start back search
			if(!search_back && forward_rules->jens_next_to_goal(temp)){
							cout << "NU SKA VI STARTA BAÅKT" << endl;
			 				//Starts back searh
							search_back = true;

							jens_start_back = temp->getCurrent_position();
							forward_stack.push( temp );
							return START_BACK;

			}
			//Check if we are in the solution
			if(forward_rules->solutionCheck(temp)){

					forward_last_node = temp;
					cout << "DONE!" << endl;

					//printBoard(temp);
					return SOLUTION_FOUND;
			}

			if(search_back){
			//Check with back search
			Node * back_node = back_rules->youHasMe(temp);
			if(back_node != NULL){
				back_last_node = back_node;
				forward_last_node = temp;
				cout << "Match" << endl;
				return SOLUTION_FOUND;
			}
			}



	forward_stack.push( temp );
	return OK;
}
int back_process(Node *n)
{
	unsigned int best_cost = -1;		// BIG value.
	unsigned int way_to_walk;
	int best_dir;
	int best_dirs[] = {-1,-1,-1,-1};								   // RANDOM WALK
	int mod = 0;

	//Set node in process
	back_rules->set_node(n);

	//Add the boxes to the board (from node in process)
	back_rules->addBoxes();

	// Go through all the four possible directions.
	for(unsigned int i = 0; i < 4; i++) {
		int enforce_return = back_rules->enforce(i);
		if( enforce_return != FAIL) {
		//cout << "Fann en bra väg! " << moves_real[i] << endl;


			// Recives a way to walk.
			way_to_walk = back_rules->heuristics(i);


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

	back_rules->removeBoxes();

	//Chose what direction to walk
	if(mod > 0)
	{
//		srand(time(0));
//		best_dir = best_dirs[rand() % mod];
		best_dir = best_dirs[0];
	}
	//We didnt find any good direction
	else{
		cout << "Back Pooop BACK" << endl;
		back_stack.pop();
		return OK;
	}

	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));
	//cout <<"kommer ga: " << moves_real[best_dir] << "dvs till " << (int) p.x << "," << (int)p.y << endl;


		cout << "Back searching "<<endl;
		Node * temp = new Node(p, n->getCurrent_position(),n,n->getBoxes(),n->getLen(), getXYDir(best_dir), revereseDir(best_dir));


		back_rules->set_node(temp);

			temp->setGoalCost(0);
			//Marks this node, or state as visited.
			back_rules->markAsVisited(temp);




			if(back_rules->solutionCheck(temp)){

					back_last_node = temp;
					cout << "DONE!" << endl;

					//printBoard(temp);
					return SOLUTION_FOUND;
			}
			//Check with forward search
			Node * forward_node = forward_rules->youHasMe(temp);
			if(forward_node != NULL){
				back_last_node = temp;
				forward_last_node = forward_node;
				cout << "Match inne i bakc!" << endl;
				return SOLUTION_FOUND;
			}

	back_stack.push( temp );
	return OK;
}


/**
 * Main
 */
int main(int argc, char ** argv)
{
	// Command-line argument handling
	string host, port, board_nr;
	boost::asio::ip::tcp::socket * socket = NULL;

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

	//Makes forward rules.
	forward_rules = new Heuristics(board_str);


	//Make root node.
	f_rootNode = forward_rules->getRootNode();

	//Appends root node to the stack.
	forward_stack.push(f_rootNode);

	int res = 0;
	//true = do forward.
	bool direction = true;
	int iterations = 0;
	while(!forward_stack.empty()){
		iterations++;
		if(direction){
			if(search_back){
			direction = false;
			}
		//printBoard(forward_stack.top());
		res = forward_process(forward_stack.top());
		if(res == FAIL || res == SOLUTION_FOUND){
			if(res == SOLUTION_FOUND){
				res = FORWARD_SOLUTION;
				cout << "forward found solution" << endl;
			}
			break;
		}
		//Start back search
		if(res == START_BACK){

			//Initiates back search
			back_rules = new BackHeuristics(board_str);
			b_rootNode = back_rules -> getRootNode();

			//This is really important!!
			b_rootNode ->setCurrent_position(jens_start_back);

			//Add the back root node
			back_stack.push(b_rootNode);
		}
		}
		//Back search
		else{
			direction = true;
			res = back_process(back_stack.top());
			if(res == FAIL || res == SOLUTION_FOUND){
				if(res == SOLUTION_FOUND){
					cout << "back found solution" << endl;
								res = BACK_SOLUTION;
								if(back_last_node == NULL){
									cout << "FAAAAAN HOORA" << endl;
									exit(0);
								}
							}
					break;
				}
		}
	}

	cout << "Iterations: " << iterations << endl;
	//res now knows which direction is the bomb
	cout << "klara" << endl;

	if(back_last_node == NULL && forward_last_node == NULL)
	{
		cerr << "FAIL: We found nothing."<< endl;
		exit(1);
	}

	string solution;

	cout << "NU JÄVLAR LÖSER VI DEN HÄR SKITENNN!!!! "<<endl<<endl;


	//BACK found solution by it sefl
	if(res == BACK_SOLUTION && forward_last_node == NULL){
		cout << "only back " << endl;
		do{
					if(back_last_node == NULL)
					{
						cout << "FAIL" << endl;
						break;
					}
					cout << "A " << back_last_node->LAST_DIR << endl;
					solution += moves_real[back_last_node->LAST_DIR] +  " ";
					cout << "AB" << endl;
					//printBoard(last_node);
					back_last_node = back_last_node->getParent();
					cout << "B" << endl << endl;


				}while(back_last_node != b_rootNode);
	}
	//Back search found a link with back
	else if(res == BACK_SOLUTION){
		cout << "fack me back to front" << endl;

		//"forward" nodes
		do{
			cout << "loopish"<<endl;
				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;
				//printBoard(last_node);
				forward_last_node = forward_last_node->getParent();


			}while(forward_last_node != f_rootNode);
		cout << "hej" << solution << endl;
		//"backwards" nodes
		do{
			if(back_last_node == NULL)
			{
				cout << "FAIL" << endl;
				break;
			}
			cout << "A " << back_last_node->LAST_DIR << endl;
			solution += moves_real[back_last_node->LAST_DIR] +  " ";
			cout << "AB" << endl;
			//printBoard(last_node);
			back_last_node = back_last_node->getParent();
			cout << "B" << endl << endl;


		}while(back_last_node != b_rootNode);

		cout << "npolllan broot" << moves_real[b_rootNode->LAST_DIR]<< endl;

		cout << "En sol:" << solution << endl;
	}
	//Only forward
	else if(res == FORWARD_SOLUTION && back_last_node == NULL){
		cout << "ONLY FORWARD " << endl;
		//"forward" nodes
		do{
			cout << "loopish"<<endl;
				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;
				//printBoard(last_node);
				forward_last_node = forward_last_node->getParent();


			}while(forward_last_node != f_rootNode);
	}
	//forward + back
	else{
		cout << "F och back!" << endl;
		//"forward" nodes
		do{
			cout << "loopish"<<endl;
				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;
				//printBoard(last_node);
				forward_last_node = forward_last_node->getParent();


			}while(forward_last_node != f_rootNode);
		cout << "hej" << solution << endl;
		//"backwards" nodes
		do{
			if(back_last_node == NULL)
			{
				cout << "FAIL" << endl;
				break;
			}
			cout << "A " << back_last_node->LAST_DIR << endl;
			solution += moves_real[back_last_node->LAST_DIR] +  " ";
			cout << "AB" << endl;
			//printBoard(last_node);
			back_last_node = back_last_node->getParent();
			cout << "B" << endl << endl;


		}while(back_last_node != b_rootNode);



	}
/*
    // Reverse the string into correct ordet.
    string::iterator pos;
    string rev_solution;
    for (pos = solution.end(); pos != solution.begin()-1; pos--) {
        rev_solution += *pos;
    }


	cout << "Solution:\t" << rev_solution << endl;
	cout <<  "No rev solution: \t" << solution << endl;
	//SOLUTION KAN ANVÄNDS FÖR BACKTRACKING.
	if (server)
	{
		// Send a solution and prints
		cout << "Server answer:\t";

		//Substring, thanks Javier!
		send(*socket, rev_solution.substr(1,rev_solution.length()));
		//send(*socket, solution);
	}
	*/
	return 0;
}
