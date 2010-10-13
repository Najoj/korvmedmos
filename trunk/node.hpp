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
		int moved_box;
		Node() {};
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walker) {
			this->len = len;
			moved_box = -1;
			boxes_positions = new Position[len];
			// Copy boxes.
			for(int i = 0; i < len; i++)
			{
				// Update boxes if needed.
				if(boxes[i] == jens) {
					moved_box = i;
				//	cout << "Uppdaterar boxar!";
					boxes_positions[i] = boxes[i] + dir;
				} else {
					boxes_positions[i] = boxes[i];
				}
			}

			// Saves Jens' posistion.
			this->jens = jens;
			// Sets parent node
			this->parent = parent;

			path_cost = 0;
			if (parent != NULL) {
				parent->LAST_DIR = walker;
			}
		}
		/**
		 * Auto genereated getter and setter methods.
		 */
		Position * getBoxes()
		{
			return boxes_positions;
		}
		
		int getPathCost() {
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
		

		Node * getParent() {
			return parent;
		}
		
		/**
		 * Hash and hash related stuff. DO NOT TOUCH!
		 */
		bool operator==(const Node & other) const
		{
			if (this->jens != other.jens)
				return false;
			
			for (int i = 0; i < len; i++)
			{
				if (this->boxes_positions[i] != other.boxes_positions[i])
				return false;
			}
			return true;
		}
		
		friend std::size_t hash_value(Node const& p)
		{
			std::size_t hash = 0;
			hash += 499973*p.jens.x + 849731*p.jens.y;
			for(int i = 0; i < p.len; i++)
			{
				hash += (612301*p.boxes_positions[i].x) & (1182463*p.boxes_positions[i].y);
			}
			return hash;
		}
		
		int getLen() {
			return len;
		}
};
#endif
