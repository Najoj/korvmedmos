#ifndef RULES_HPP
#define RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>
#include <cmath>

#include "Board.hpp"
#include "heuristics.hpp"
#include "node.hpp"
#include "common.hpp"

class Rules: protected Heuristics{
private:
	bool box_into_wall();
	bool box_into_box();
	bool jens_into_box();
	bool jens_into_wall();
	bool box_into_deadlock();
	bool been_in_node(Node * node);

	typedef boost::unordered_set<Node> NodeSet;
	NodeSet visited_nodes;

	Board * board;

	Node * node_in_process;
	Position  new_position;

	int w_dir;

	void addBoxes();
	void removeBoxes();
	
	int length_from_jens_to_box(int dir, Node * parent)
	{
		int cost = 0;
		
		Position new_jens = parent->getCurrent_position();
		
		int min = BIG_VALUE;
		int min_i = 0; // i-värdet för minsta boxen
		int save;
		if(dir == UP)
		{
			new_jens.y--;
		}
		else if(dir == RIGHT)
		{
			new_jens.x++;
		}
		else if(dir == DOWN)
		{
			new_jens.y++;
		}
		else // (dir == LEFT)
		{
			new_jens.x--;
		}
		
		for(int i = 0; i < parent->getLen(); i++)
		{
			save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
			if(save < min)
			{
				min = save;
				min_i = i;
			}
		}
		cost += min;
		if (board->get(parent->getBoxes()[min_i]) == GOAL) {
			cost += 5;
		}
		
		return cost;
	}
	

	int jens_box_goal_distance(int dir, Node * parent)
	{
		bool debug = false;
		int debug_nr = 0;
		node_in_process = parent;
		addBoxes();
		int min = -1, save, push_box_dir;
		Position nearest_box, nearest_goal;
		Position temp;
		int save_x, save_y,jens_to_push_box_dir, box_to_goal_distance;
		int cost = 0;
		Position new_jens = parent->getCurrent_position(); 


		if(board->get(new_jens) == BOX_ONGOAL){
			cost += COST_TO_MOVE_BOX_ON_GOAL;
		}



		for(int i = 0; i < parent->getLen(); i++)
		{
			temp = parent->getBoxes()[i];
			save = Heuristics::length_to_box(new_jens, temp);
			
			if(board->get(temp) != BOX_ONGOAL && save < min)
			{
				min = save;
				nearest_box = temp;
			}
		}		
		for(int i = 0; i < parent->getLen(); i++)
		{
			temp = board->goals[i];
			save = Heuristics::length_to_box(nearest_box, temp);
			
			if(board->get(temp) != BOX_ONGOAL && save < min)
			{
				min = save;
				nearest_goal = temp;
			}
		}		
		
		box_to_goal_distance = min;
		if( abs((float) nearest_goal.x - nearest_box.x) < abs((float) nearest_goal.y - nearest_box.y))
		{
			if( nearest_goal.x - nearest_box.x > 0 )
				push_box_dir = RIGHT;
			else // nearest_goal.x - nearest_box.x <= 0
				push_box_dir = LEFT;
				
		}	
		else if( abs((float) nearest_goal.x - nearest_box.x) >= abs((float) nearest_goal.y - nearest_box.y))
		{
			if( nearest_goal.y - nearest_box.y > 0 )
				push_box_dir = DOWN;
			else // nearest_goal.y - nearest_box.y <= 0
				push_box_dir = UP;
		}
		else
		{
			cout << "WUT THE FUKK" << endl;
		}		
		if(push_box_dir == RIGHT)
			temp = nearest_box.getDirection(LEFT);
		else if(push_box_dir == LEFT)
			temp = nearest_box.getDirection(RIGHT);
		else if(push_box_dir == UP)
			temp = nearest_box.getDirection(DOWN);
		else if(push_box_dir == DOWN)
			temp = nearest_box.getDirection(UP);			
		jens_to_push_box_dir = Heuristics::length_to_box(new_jens, temp);
		cost += jens_to_push_box_dir;
		cost += box_to_goal_distance; 	


		
		removeBoxes();
		
		return cost;
	}
		
public:

	Rules(std::string board){
		readBoard(board);
		improve_board(this->board);
	}
	int enforce(int dir, Node * parent){
		w_dir = dir;
		bool jens_pushing_box = false;
		//node_in_process = parent;
		//new_position = node_in_process->getCurrent_position().getDirection(dir);
		//Anropa en jävla massa privata metoder

		node_in_process = parent;
		//CLASSIC JAKE HAXX!
		new_position = (node_in_process->getCurrent_position().getDirection(dir));

		//CLASSIC TIM HAXX!
		//Insert boxes.
		addBoxes();

		//If jens is walking into a wall return fail.
		if(jens_into_wall()){
				removeBoxes();
				return FAIL;
		}
		//Is JENS walking into a box?
		if(jens_into_box()){

			//see if we can push this box.
			if( ! (box_into_wall() && box_into_box() && box_into_deadlock())){
					removeBoxes();
//					cout << "EN VÄGG!!" << endl;
					return FAIL;
				}else{
					jens_pushing_box = true;
				}


		}
		Position p(new_position.x, new_position.y);
		Node * n = new Node(p, parent,parent->getBoxes(),parent->getLen(), Position(0,0).getDirection(w_dir), dir);
		
		if(been_in_node(n))
		{
			removeBoxes();
			return FAIL;
		}

		removeBoxes();
		if(jens_pushing_box){
			return JENS_IS_PUSHING_BOX_OK;
		}else{
			return OK;
		}
	}

	int heuristics(int dir, Node * parent, int enforce_return){
		int cost = 0;
		//																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									cout << "HEURISTICS" << endl;		
		//cost += length_from_jens_to_box(dir, parent);
		cost += jens_box_goal_distance(dir,parent);
		
		return cost;
	}

	void markAsVisited(Node * n){
		visited_nodes.insert(*n);
	}
	bool readBoard(std::string boardIn);

	Node getRootNode();
	void printBoard(Node * node);

	bool solutionCheck(Node * n);

};

#endif


