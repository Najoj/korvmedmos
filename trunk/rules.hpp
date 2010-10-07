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
	bool been_in_node(Node * node);

	typedef boost::unordered_set<Node> NodeSet;
	NodeSet visited_nodes;

	Board * board;

	Node * node_in_process;
	Position  new_position;

	int w_dir;

	void addBoxes();
	void removeBoxes();
public:

	Rules(std::string board){
		readBoard(board);
		improve_board(this->board);
	}
	int enforce(int dir, Node * parent){
		w_dir = dir;
		//node_in_process = parent;
		//new_position = node_in_process->getCurrent_position().getDirection(dir);
		//Anropa en jävla massa privata metoder

		node_in_process = parent;
		//CLASSIC JAKE HAXX!
		new_position = (node_in_process->getCurrent_position().getDirection(dir));

		//CLASSIC TIM HAXX!
		addBoxes();

		//Add boxes to the board.
		board->insert_boxes(node_in_process->getBoxes(), parent->getLen());

		//If jens is walking into a wall return fail.
		if(jens_into_wall()){
				removeBoxes();
				return FAIL;
		}
		//Is JENS walking into a box?
		if(jens_into_box()){

			//see if we can push this box.
			if( ! (box_into_wall() && box_into_box())){
					removeBoxes();
					cout << "BOX push fail";
					return FAIL;
				}else{
					cout << "============== VI FLYTTAR BOX!" << endl;
				}


		}
		Position p(new_position.x, new_position.y);
		Node * n = new Node(p, parent,parent->getBoxes(),parent->getLen(), Position(0,0).getDirection(w_dir) );
		
		if(been_in_node(n))
		{
			removeBoxes();
			return FAIL;
		}

		removeBoxes();
		
		return OK;
	}

	int heuristics(int dir, Node * parent){
		int cost = 0;
		
		Position new_jens = parent->getCurrent_position();
		
		int min = BIG_VALUE;
		int save;
		if(dir == UP)
		{
			new_jens.y--;
			for(int i = 0; i < parent->getLen(); i++)
			{
				save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
				if(save < min)
					min = save;
			}
		}
		else if(dir == RIGHT)
		{
			new_jens.x++;
			for(int i = 0; i < parent->getLen(); i++)
			{
				save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
				if(save < min)
					min = save;
			}
		}
		else if(dir == DOWN)
		{
			new_jens.y++;
			for(int i = 0; i < parent->getLen(); i++)
			{
				save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
				if(save < min)
					min = save;
			}
		}
		else // (dir == LEFT)
		{
			new_jens.x--;
			for(int i = 0; i < parent->getLen(); i++)
			{
				save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
				if(save < min)
					min = save;
			}
		}
		cost += min;
		
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
