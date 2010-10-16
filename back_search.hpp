/*
 * back_search.hpp
 *
 *  Created on: 16 okt 2010
 *      Author: jacob
 */

#ifndef BACK_SEARCH_HPP_
#define BACK_SEARCH_HPP_
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <queue>

#include "back/back_heuristics.hpp"
#include "back/back_rules.hpp"

#include "node.hpp"
#include "forward_search.hpp"
using namespace std;
using namespace boost;

class BackSearch{
public:
    BackSearch(string board_str, Position jens): m_stoprequested(false){

    	rules = new BackHeuristics(board_str);

        iterations = 0;

    	// Make the root node, this will be pushed onto stack later on!
    	rootNode = rules->getRootNode();


    	rootNode->setCurrent_position(jens);

    	rules->set_node(rootNode);
    	rules->addBoxes();
    	rules->printBoard(rootNode);
    	rules->markAsVisited(rootNode);
    	stack.push(rootNode);

    	cout << "genom herr konstruktor "<<endl;

    	forward=NULL;
    }

    ~BackSearch(){
    	delete rules;
    }

    void setForwardRules(Rules *r){
    	forward = r;
    }

    // Create the thread and start work
    void go()
    {
        assert(!m_thread);
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&BackSearch::search, this)));

    }

    void stop() // Note 1
    {
        assert(m_thread);
        m_stoprequested = true;
        m_thread->join();
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



    BackHeuristics * getRules(){
    	return rules;
    }
private:



    BackHeuristics *rules;

    priority_queue<Node*> stack;

    int iterations;

    Node * last_node;
    Node * rootNode;

    //Used to acces hash set in the other thread
    Rules * forward;

    bool solution_found;

    // This is the static class function that serves as a C style function pointer
    // for the pthread_create call
    static void start_thread(void *obj)
    {
        //All we do here is call the do_work() function
        reinterpret_cast<BackSearch *>(obj)->search();
    }
    volatile bool m_stoprequested;
    boost::shared_ptr<boost::thread> m_thread;
    boost::mutex m_mutex;

    std::vector<int> m_fibonacci_values;


/*''
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
   		///cout << "Fann en bra väg! " << moves_real[i] << endl;


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



			temp = new Node(p,n->getCurrent_position(), n,n->getBoxes(),n->getLen(), getXYDir(best_dir), revereseDir(best_dir));


   			rules->set_node(temp);
   			//rules->addBoxes();

   			//rules->printBoard(temp);
   		//	temp->setGoalCost(rules->total_goal_distance(temp));
   			temp->setGoalCost(0);
   			//Marks this node, or state as visited.
   			rules->markAsVisited(temp);

   			//Clears the board from boxes
   			//rules->removeBoxes();

   			if(rules->solutionCheck(temp) /*|| forward->youHasMe(temp) != NULL*/){

   					last_node = temp;
   					cout << "BACK search DONE!" << endl;

   					return true;
   			}


   	stack.push( temp );
   	return false;


       }


    // Compute and save fibonacci numbers as fast as possible
    int search()
    {

    	cout << "root nod "<< stack.size() << endl;
    	    	rules->set_node(stack.top());
    	    	rules->addBoxes();
    	    	rules->printBoard(stack.top());
    	    	rules->removeBoxes();

    	        //Run as long as we should and stack not empty
    	        while (!m_stoprequested || !stack.empty()){

    	        	//Stops if found solution
    	        	if(process(stack.top())){
    	        		break;
    	        	}
    	        	cout << "BACK SEARCH: Iteration: " << iterations << endl;
    	        	rules->set_node(stack.top());
    	        	rules->addBoxes();
    	        	rules->printBoard(stack.top());
    	        	rules->removeBoxes();
    	        	cout << endl << endl;
    	        	iterations++;


    	          /*  int value = fibonacci_number(iteration);
    	            boost::mutex::scoped_lock l(m_mutex);
    	            m_fibonacci_values.push_back(value);*/
    	        }
    	        cout << "BS thread stopped" << endl;
    	        solution_found  = true;
    	        return 1;

        //Prints solution
    }
};
#endif /* BACK_SEARCH_HPP_ */
