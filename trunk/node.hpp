/**
 * node.hpp
 *
 * 
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
		// Position of player, Jens.
		Position jens;
		
		// Used direction of, that is the nodes childrens directions.
		char used_directions[4];
		
		// Length of the board matrix
		char len;
		
		// Pointer to boxes positions.
		Position * boxes_positions;
		
		// Path cost
		int path_cost;
		
		// Parent of the node
		Node * parent;
		
		Node * getChildDirection(int dir);
		
		bool deadlock(Position pos, Position parent);
		
	public:
		unsigned char LAST_DIR;
		
		Node() {};
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walked);
		
		/**
		 * Auto genereated getter and setter methods.
		 */
		Position * getBoxes()
		{
			return boxes_positions;
		}
		int getPathCost()
		{
			return path_cost;
		}
		void move_box(int i, Position p)
		{
		    boxes_positions[i] = p;
		}
		Position getCurrent_position()
		{
			return jens;
		}
		void setCurrent_position(Position jens)
		{
			this->jens = jens;
		}
		Node * getParent()
		{
			return parent;
		}
		int getLen()
		{
			return len;
		}
		/**
		 * Hash and hash related stuff. DO NOT TOUCH!
		 */
		bool operator==(const Node & other) const;
		friend std::size_t hash_value(Node const& p);
};
#endif
