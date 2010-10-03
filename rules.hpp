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
public:

	Rules(std::string board){
		readBoard(board);
	}
	int enforce(int dir, Node * parent){
		//Anropa en jävla massa privata metoder
		return 0;
	}

	int heuristics(int dir, Node * parent){
		return 0;
	}
	bool readBoard(std::string boardIn);

	Node getRootNode();
	void printBoard(Node * node);

};

#endif
