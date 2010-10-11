#ifndef RULES_HPP
#define RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>
#include <cmath>

#include "Board.hpp"
#include "heuristics.hpp"
#include "node.hpp"
#include "common.hpp"

class Rules:public Heuristics{
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
	void addGoals();
	int length_from_jens_to_box(int dir, Node * parent);

	int jens_box_goal_distance(int dir, Node * parent);

	int box_goal_distance(Node * parent, Position &jens);
		
public:

	Rules(std::string board){
		readBoard(board);
		improve_board(this->board);
	}
	int enforce(int dir, Node * parent);


	int heuristics(int dir, Node * parent, int enforce_return);

	//A heuristic.
	int total_goal_distance(Node * parent);

	void markAsVisited(Node * n){
		visited_nodes.insert(*n);
	}
	bool readBoard(std::string boardIn);

	Node getRootNode();
	void printBoard(Node * node);

	bool solutionCheck(Node * n);

};

#endif


