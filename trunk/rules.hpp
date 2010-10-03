/**
 * rules.hpp
 *
 * 
 */

#ifndef RULES_HPP
#define RULES_HPP

#include <boost/unordered_set.hpp>
#include <vector>

#include "Board.hpp"
#include "heuristics.hpp"
#include "node.hpp"
#include "common.hpp"

class Rules: protected Heuristics {
private:
	bool box_into_wall();
	bool box_into_box();
	bool jens_into_box();
	bool jens_into_wall();
	bool been_in_node(Node * node);
	
	typedef boost::unordered_set<Node> NodeSet;
	NodeSet visited_nodes;
	
	Board * board;
public:
	bool readBoard(std::string boardIn);
	Node getRootNode();
	void printBoard(Node * node);
	
	Rules(std::string board) {
		readBoard(board);
	}
	
	/**
	 * Checks if direction we want to go is accepted by the fundamental rules
	 * of Sokoban. An example would be not going into the wall.
	 */
	int enforce(int dir, Node * parent) {
		// We should call alot of private methods here.
		return 0;
	}
	/**
	 * Checks if direction we want to go is accepted by the our heuristic rules
	 * to make the search speed up. An example would be not pushing a box into a
	 * corner, where the player then can not move it the box anywhere else.
	 */
	int heuristics(int dir, Node * parent) {
		return 0;
	}
};
#endif
