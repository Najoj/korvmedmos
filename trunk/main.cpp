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
#include "forward_heuristics.hpp"
#include "back/back_heuristics.hpp"
#include "common.hpp"



using namespace std;

ForwardHeuristics * forward_rules;
BackHeuristics *back_rules;

//Forward root node generated  by forward rules
Node * f_rootNode;
//Backroot node genereate by back rules
Node * b_rootNode;

bool search_back = false;

Position jens_start_back;
string board_str;

//Refrence to the final node in back search (the goal state)
Node * back_last_node = NULL;
//Refrence to the first node in back search

Node * back_start = NULL;
//Refrence to the last node in a forward search (the goal state)
Node * forward_last_node = NULL;

int iterations = 0;


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


/**
 * Processes the node, basically in tries to make a child of the give node
 * using the the forward search
 */
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
	//	best_dir = best_dirs[rand() % mod];
		best_dir = best_dirs[0];
	}
	//We didnt find any good direction
	else{

		forward_stack.pop();
		return OK;
	}

	Position p = n->getCurrent_position();

	p.addPosition(getXYDir(best_dir));




	Node * temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);


	forward_rules->set_node(temp);
	forward_rules->addBoxes();

	//Sets the priority the priority queue
	temp->setGoalCost(forward_rules->total_goal_distance(temp));

	//Marks this node, or state as visited.
	forward_rules->markAsVisited(temp);

	//Clears the board from boxes
	forward_rules->removeBoxes();

	//Check if we want to start back search
	if(!search_back && forward_rules->jens_next_to_goal(temp)){

		//Starts back searh
		search_back = true;

		jens_start_back = temp->getCurrent_position();//temp->getCurrent_position();

		forward_stack.push( temp );
		return START_BACK;

	}
	//Check if we are in the solution
	if(forward_rules->solutionCheck(temp)){

		forward_last_node = temp;
		cout << "DONE! - Forward search found solution" << endl;
		return SOLUTION_FOUND;
	}

	//Check with back searh only if we have started back search
	if(search_back){
			//Check with back search
		Node * back_node = back_rules->youHasMe(temp);
		if(back_node != NULL){
			back_last_node = back_node;
			forward_last_node = temp;
			cout << "Match Done" << endl;
			return SOLUTION_FOUND;
		}
	}



	forward_stack.push( temp );
	return OK;
}
/**
 * Processes the node, basically in tries to make a child of the give node
 * using the the back search, essentially the same as process forward.
 */
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

		//Finds a valid direction
		int enforce_return = back_rules->enforce(i);
		if( enforce_return != FAIL) {


			// Calculates the cost for this direction
			way_to_walk = back_rules->heuristics(i);


			// Checks if the direction is the best
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
	//	srand(time(0));
	//	best_dir = best_dirs[rand() % mod];
		best_dir = best_dirs[0];
	}
	//We didnt find any good direction
	else{
		//cout << "Back Pooop BACK" << endl;
		back_stack.pop();
		return OK;
	}

	//Calculates jens new position
	Position p = n->getCurrent_position();
	p.addPosition(getXYDir(best_dir));

	//Builds the actual child, note that this is the back constructor.
	Node * temp = new Node(p, n->getCurrent_position(),n,n->getBoxes(),n->getLen(), getXYDir(best_dir), revereseDir(best_dir));


	//This is used to total_goal_distance_calculations
	//back_rules->set_node(temp);
//	back_rules->addBoxes();

	//Sets the priority in A* star.
	//temp->setGoalCost(back_rules->total_goal_distance(temp));
	temp->setGoalCost(0);
	//Marks this node, or state as visited.
	back_rules->markAsVisited(temp);
	//back_rules->removeBoxes();



	//See if we found a solution
	if(back_rules->solutionCheck(temp)){

		back_last_node = temp;
		cout << "DONE! - Back search found a solution" << endl;

		//printBoard(temp);
		return SOLUTION_FOUND;
	}
			//Check with forward search
			Node * forward_node = forward_rules->youHasMe(temp);
			if(forward_node != NULL){
				back_last_node = temp;
				forward_last_node = forward_node;
				//cout << "Match inne i bakc!" << endl;
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
	forward_rules = new ForwardHeuristics(board_str);


	//Make root node.
	f_rootNode = forward_rules->getRootNode();

	//Appends root node to the stack.
	forward_stack.push(f_rootNode);

	int res = 0;
	//true = do forward.
	bool direction = true;
	while(!forward_stack.empty()){
		iterations++;
		//cout << "iter: " << iterations << endl;
		if(direction){
			if(search_back){
			direction = false;
			}
		//printBoard(forward_stack.top());
		res = forward_process(forward_stack.top());
		if(res == FAIL || res == SOLUTION_FOUND){
			if(res == SOLUTION_FOUND){
				res = FORWARD_SOLUTION;
			//	cout << "forward found solution" << endl;
			}
			break;
		}
		//Start back search
		if(res == START_BACK){

			cout << "Starting back search:  " << iterations  << endl;
			//Initiates back search
			back_rules = new BackHeuristics(board_str);
			b_rootNode = back_rules -> getRootNode();

			//This is really important!! Otherwise he will start at the wrong position
			b_rootNode ->setCurrent_position(jens_start_back);

			//Add the back root node
			back_stack.push(b_rootNode);

			back_start = forward_stack.top();
		}
		}
		//Back search
		else if(!back_stack.empty()){
			direction = true;
			res = back_process(back_stack.top());
			if(res == FAIL || res == SOLUTION_FOUND){
				if(res == SOLUTION_FOUND){
					cout << "back found solution" << endl;
								res = BACK_SOLUTION;

							}
					break;
				}
		}
		//Back stack was empty, so lets try to restart, the start pos was probably bad.
		else{
			search_back = false;
			direction = true;
			cout << "Restart back " << endl;
			//cout << "Back search have probably failed "<< endl;
		}
	}

	cout << "Iterations: " << iterations << endl;


	if(back_last_node == NULL && forward_last_node == NULL)
	{
		cerr << "FAIL: We found nothing."<< endl;
		exit(1);
	}

	string solution;



	/**
	 * Builds the solution horrible code..Bascially it tries to follow parent pointer in the node class
	 */

	//BACK found solution by it sefl
	if(res == BACK_SOLUTION && forward_last_node == NULL){

		//"forward" nodes


				//"backwards" nodes
				do{


					solution += moves_real[back_last_node->LAST_DIR] +  " ";

					back_last_node = back_last_node->getParent();



				}while(!(*back_last_node == *b_rootNode));


	}
	//Back search found a link with forward
	else if(res == BACK_SOLUTION){


		//"forward" nodes
		do{
;
				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;

				forward_last_node = forward_last_node->getParent();


			}while(!(*forward_last_node == *f_rootNode));

		//"backwards" nodes
		do{


			solution += moves_real[back_last_node->LAST_DIR] +  " ";

			back_last_node = back_last_node->getParent();



		}while(!(*back_last_node == *b_rootNode));


	}
	//Only forward
	else if(res == FORWARD_SOLUTION && back_last_node == NULL){

		//"forward" nodes
		do{

				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;
				//printBoard(last_node);
				forward_last_node = forward_last_node->getParent();


			}while(!(*forward_last_node == *f_rootNode));
	}
	//forward + back
	else{

		//"forward" nodes
		do{

				//Reverse the solution
				solution = moves_real[forward_last_node->LAST_DIR] +  " " + solution;
				//printBoard(last_node);
				forward_last_node = forward_last_node->getParent();


			}while(!(*forward_last_node == *f_rootNode));
;
		//"backwards" nodes
		do{


			solution += moves_real[back_last_node->LAST_DIR] +  " ";

			//printBoard(last_node);
			back_last_node = back_last_node->getParent();
;


		}while(!(*back_last_node == *b_rootNode));



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
