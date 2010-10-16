/*
 * forward_search.hpp
 *
 *  Created on: 16 okt 2010
 *      Author: jacob
 */

#ifndef FORWARD_SEARCH_HPP_
#define FORWARD_SEARCH_HPP_


#include <string>
#include <queue>

#include "heuristics.hpp"
#include "rules.hpp"

#include "node.hpp"

#include "back_search.hpp"

using namespace std;
using namespace boost;
class ForwardSearch{
public:
    ForwardSearch(string board_str){

    	rules = new Heuristics(board_str);

        iterations = 0;

    	// Make the root node, this will be pushed onto stack later on!
    	rootNode = rules->getRootNode();

    	/**
    	 * TODO: REMOVE THIS
    	 */
    	//rootNode.setCurrent_position(Position(5,2));

    	rules->set_node(rootNode);
    	rules->addBoxes();
    	rules->printBoard(rootNode);
    	rules->removeBoxes();
    	rules->markAsVisited(rootNode);
    	stack.push(rootNode);

    	solution_found=false;

    	last_node = NULL;
    	backward = NULL;

    	start_back = false;

    }

    ~ForwardSearch(){
    	delete rules;
    }

    void setBackRules(BackRules *br){
    	backward = br;
    }


   /* int get_fibonacci_value(int which)
    {
        boost::mutex::scoped_lock l(m_mutex); //Note 2
        return m_fibonacci_values.get(which);
    }*/



    void setFound(){
    	solution_found = true;


    }

    bool getFound(){
    	return solution_found;
    }

    Node * getLast(){
    	return last_node;
    }

    Node gotRoot(){
    	return *rootNode;
    }

    Heuristics * getRules(){
    	return rules;
    }
    bool startBack(){
    	return start_back;
    }

    Position jens_s_back;
    int search(){


    	process(stack.top());

    	cout << "Forward hej: "<< stack.size() << endl;
    	rules->set_node(stack.top());
    	rules->addBoxes();
    	rules->printBoard(stack.top());
    	rules->removeBoxes();

    	if(stack.empty()){
    		return FAIL;
    	}
    	return OK;


        //Prints solution
    }
private:


    Heuristics *rules;

    priority_queue<Node*> stack;

    Node *last_node;
    int iterations;

    BackRules * backward;

    Node * rootNode;
    bool solution_found;


    bool start_back;



    /**
     * Returns true when we found a solution
     */
    bool process(Node * n){

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
		//cout << "Fann en bra väg! " << moves_real[i] << endl;


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
//cout <<"kommer ga: " << moves_real[best_dir] << "dvs till " << (int) p.x << "," << (int)p.y << endl;



	Node *temp;



			temp = new Node(p, n,n->getBoxes(),n->getLen(), getXYDir(best_dir), best_dir);

			//Check if we have started back search
			if(start_back){
				if(backward!=NULL){
				//	mutex::scoped_lock l(m_mutex); eller?
					//We found a solution!!
				/*	if(backward->youHasMe(temp) != NULL){
						cout << "forward done!";
						exit(0);
						return true;
					}*/
				}

			}
			//Check if we should start back search
			else if(rules->jens_next_to_goal(temp)){
				cout << "NU SKA VI STARTA BAÅKT" << endl;
 				//Starts back searh
				start_back = true;

				jens_s_back = temp->getCurrent_position();

			}


			rules->set_node(temp);
			//rules->addBoxes();

			//rules->printBoard(temp);
		//	temp->setGoalCost(rules->total_goal_distance(temp));
			temp->setGoalCost(0);
			//Marks this node, or state as visited.
			rules->markAsVisited(temp);

			//Clears the board from boxes
			//rules->removeBoxes();

			if(rules->solutionCheck(temp)){

					//mutex::scoped_lock l(m_mutex);
					last_node = temp;
					solution_found = true;
					cout << "Forward search DONE!" << endl;
					return true;
			}


	stack.push( temp );
	return false;


    }



};
#endif /* FORWARD_SEARCH_HPP_ */
