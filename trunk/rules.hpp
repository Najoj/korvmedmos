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
	bool box_into_boxlock();
	bool jens_into_box();
	bool jens_into_wall();
	bool box_into_deadlock();
	bool been_in_node(Node * node);

	typedef boost::unordered_set<Node> NodeSet;
	NodeSet visited_nodes;

	Node * node_in_process;
	Position  new_position;

	int w_dir;
	
	int length_from_jens_to_box(int dir, Node * parent);

	int jens_box_goal_distance(int dir);
		
public:
	Rules(std::string board){
		readBoard(board);
		improve_board(this->board);
		visited_nodes = NodeSet(3000000);
	}
	Board * board;
	void addBoxes();
	void removeBoxes();
	int enforce(int dir);

	int heuristics(int dir);

	void markAsVisited(Node * n){
		visited_nodes.insert(*n);
	}
	bool readBoard(std::string boardIn);
	void set_node(Node * node) { node_in_process = node; };
	Node getRootNode();
	void printBoard(Node * node);

	bool solutionCheck(Node * n);

};

#endif


