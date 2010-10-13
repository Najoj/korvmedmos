/**
* node.hpp
*/

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "common.hpp"

using namespace std;

class Board;

class Node{
	private:
		/* Variables */
		Position jens; // Position of player, Jens.
		// Used direction of, that is the nodes childrens directions.
		char used_directions[4];
		char len; // Number of boxes
		Position * boxes_positions; // Pointer to boxes positions.
		int path_cost; // Path cost
		Node * parent; // Parent of the node
		
		/* Functions */
		Node * getChildDirection(int dir);
		bool deadlock(Position pos, Position parent);
	public:
		unsigned char LAST_DIR;
		Node() {};
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walked);
		Position * getBoxes();
		Position getCurrent_position();
		Node * getParent();
		void move_box(int i, Position p);
		void setCurrent_position(Position jens);
		int getLen();
		int getPathCost();
		bool operator==(const Node & other) const;
		friend size_t hash_value(Node const & p);
};
#endif
