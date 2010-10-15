/*
 * back_heuristics.hpp
 *
 *  Created on: 15 okt 2010
 *      Author: jacob
 *  Desc: Used for reverese lookup rules enforcment.
 */

#ifndef BACK_RULES_HPP
#define BACK_RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>
#include <cmath>

#include "../Board.hpp"

#include "../node.hpp"
#include "../common.hpp"

class BackRules{

private:
	//Functions used to enforce the basic rules.
	bool box_into_wall();
	bool box_into_box();

	bool jens_into_box();
	bool jens_into_wall();



protected:


	bool box_into_deadlock();


	bool been_in_node(Node * node);
	int box_goal_distance(Node * parent, Position &jens);

	typedef boost::unordered_set<Node> NodeSet;
	NodeSet visited_nodes;

	Node * node_in_process;
	Position  new_position;

	int w_dir;


	Position new_position_box;
	Board * board;

	//int jens_box_goal_distance(int dir);

public:
	BackRules(std::string board){
		readBoard(board);

		visited_nodes = NodeSet(10000000);
	}
	void clear_hash()
	{
		visited_nodes.clear();
	}

	void addBoxes();
	void removeBoxes();
	int enforce(int dir);



	void markAsVisited(Node * n){
		visited_nodes.insert(*n);
	}
	bool readBoard(std::string boardIn);
	void set_node(Node * node) {
		node_in_process = node;
	};
	Node getRootNode();
	void printBoard(Node * node);

	bool solutionCheck(Node * n);

	int length_to_box(Position jens, Position box);
	//friend class Heuristics;

};

#endif


