/**
 * rules.hpp
 */

#ifndef RULES_HPP
#define RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>
#include <cmath>

#include "Board.hpp"
#include "node.hpp"
#include "common.hpp"

class Rules {
private:
	//Functions used to enforce the basic rules.
	bool box_into_wall();
	bool box_into_box();
	bool jens_into_box();
	bool jens_into_wall();
	
protected:
	bool box_into_boxlock();
	bool box_into_deadlock();
	bool been_in_node(Node * node);
	
	int box_goal_distance(Node * parent, Position &jens);
	int w_dir;
	
	typedef boost::unordered_set<Node> NodeSet;
	
	NodeSet visited_nodes;
	Node * node_in_process;
	
	Position  new_position;
	
public:
	Rules(std::string board)
	{
		// Reading board
		readBoard(board);
		// Making our NodeSet.
		visited_nodes = NodeSet(10000000);
	}
	
	// Our board
	Board * board;
	// Ugly method to add boxes into the code.
	void addBoxes();
	// 
	void removeBoxes();
	int enforce(int dir);
	
	void markAsVisited(Node * n)
	{
		visited_nodes.insert(*n);
	}

	void set_node(Node * node)
	{
		node_in_process = node;
	};
	 
	Node getRootNode();
	
	bool readBoard(std::string boardIn);
	void printBoard(Node * node);
	bool solutionCheck(Node * n);
	int length_to_box(Position jens, Position box);
};


#endif


