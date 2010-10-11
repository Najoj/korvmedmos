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
		
		Node();
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walked);
		
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
		int getPathCost() const{
			return path_cost;
		}
		void setPathCost(int p){
			path_cost = p;
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
		
		void print()
		{
			cout << "================="<<endl;
			cout << "JENS POS: " << jens.x << " " << jens.y << endl;
			for(int i = 0; i < len; i++)
			{
				cout << "BOXES" << boxes_positions[i].x << " " << boxes_positions[i].y  << endl;
				/*if(boxes_positions[i].x == 6 && boxes_positions[i].y == 3) {
				cout << "LÖSTE DET!" << endl;
				exit(0);
				}*/
			}
			cout << "================="<<endl;
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
		
		/**
		 * Ey leen!!
		 */
		int getLen() {
			return len;
		}


		bool operator() ( Node& left_hs,  Node& right_hs) const
		  {
		    	return (left_hs.getPathCost()>right_hs.getPathCost());

		  }
		bool operator<( const Node & other) const
		{
			return this->getPathCost() > other.getPathCost();
		}
};
#endif
