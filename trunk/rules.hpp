#ifndef RULES_HPP
#define RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>

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
		int min, save;
		Position nearest_box, nearest_goal;
		
		for(int i = 0; i < parent->getLen(); i++)
		{
			save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
			
			if(save < min)
			{
				min = save;
				nearest_box = parent->getBoxes()[i];
			}
		}
		
		
		
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
		
		cost += length_from_jens_to_box(dir, parent);
		cost += ();
		
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
