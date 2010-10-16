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
		//char used_directions[4];
		
		// Length of the board matrix
		char len;
		
		// Pointer to boxes positions.
		Position * boxes_positions;
		
		// Path cost
		int path_cost;
		
		// Goal cost
		int goal_cost;

		// Parent of the node
		Node * parent;
		
		Node * getChildDirection(int dir);
		
		bool deadlock(Position pos, Position parent);


	public:
		unsigned char LAST_DIR;

		Node() {};
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walker) {
			this->len = len;

			boxes_positions = new Position[len];
			// Copy boxes.
			for(int i = 0; i < len; i++)
			{
				// Update boxes if needed.
				if(boxes[i] == jens) {
				//	cout << "Uppdaterar boxar!";
					boxes_positions[i] = boxes[i] + dir;
				} else {
					boxes_positions[i] = boxes[i];
				}
			}

			// Saves Jens' posistion.
			this->jens = jens;

			// Set goal cost.
			this->goal_cost = 0;

			// Sets parent node
			this->parent = parent;

			this->path_cost = 0;


			this->LAST_DIR = walker;
			if(parent != NULL){
				this->path_cost = parent->getPathCost()+1;
			}
		}
		/**
		 * This constructor is used for back search only
		 */
		Node(Position jens, Position m_box, Node * parent, Position *boxes, int len, Position dir, int walker) {
			this->len = len;


			boxes_positions = new Position[len];

			Position tmp;
			// Copy boxes.
			for(int i = 0; i < len; i++)
			{
				//tmp = boxes[i] + dir;
				// Update boxes if needed.
				if(boxes[i] + dir == m_box) {
				//	cout << "Uppdaterar boxar!";
					boxes_positions[i] = boxes[i] + (dir);
				} else {
					boxes_positions[i] = boxes[i];
				}
			}

			// Saves Jens' posistion.
			this->jens = jens;

			// Set goal cost.
			this->goal_cost = 0;

			// Sets parent node
			this->parent = parent;

			this->path_cost = 0;


			this->LAST_DIR = walker;
			if(parent != NULL){
				this->path_cost = parent->getPathCost()+1;
			}
		}


		Node(const Node& n){
			this->jens = n.jens;
			this->goal_cost = n.goal_cost;
			this->path_cost = n.path_cost;

			this->parent = n.parent;
			this->len = n.len;

			this->boxes_positions = new Position[this->len];
			for(int i = 0; i < len; i++){
				this->boxes_positions[i] = n.boxes_positions[i];
			}

			this->LAST_DIR = n.LAST_DIR;
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
	    int getPathCost() const{
			return path_cost;
		}
	    int getGoalCost(){
	    	return goal_cost;
	    }
	    int getGoalCost() const{
	    	return goal_cost;
	    }
		Position getCurrent_position()
		{
			return jens;
		}
		
		void setParent(Node * n ){
			this->parent = n;
		}
		void setCurrent_position(Position jens)
		{
			this->jens = jens;
		}
		
		void setGoalCost(int g){
			this->goal_cost = g;
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
				hash += (612301*(p.boxes_positions[i].x<<i)) ^ (1182463*p.boxes_positions[i].y);
			}
			return hash;
		}

		int getLen() {
			return len;
		}
		 bool operator<( const Node & other) const
		{
			 // > like BFS
				return this->getPathCost()+this->getGoalCost() < other.getPathCost()+other.getGoalCost();
		}
};
#endif
