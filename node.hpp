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
		// Position of player.
		Position jens;
		

		short used_directions[4];
		
		int len;
		// Pointer to boxes positions.
		Position * boxes_positions;

		//Path lenght
		int path_cost;

		//Parent
		Node * parent;
		Node  * getChildDirection(int dir/*, int xdir, int ydir*/);

		bool deadlock(Position pos, Position parent);
	public:
		Node();
		Node(Position jens, Node * parent, Position *boxes, int len, Position dir);



		/**
		* Auto genereated getter and setter methods.
		*/
		Position * getBoxes()
		{
			return boxes_positions;
		}
		
		int getPathCost(){
			return path_cost;
		}
		Position getCurrent_position()
		{
			return jens;
		}
		
		
		void setCurrent_position(Position jens)
		{
			this->jens = jens;
		}
		

		Node * getParent(){
			return parent;
		}
		
		void print()
		{
			cout << "================="<<endl;
			cout << "JENS POS: " << jens.x << " " << jens.y << endl;
			for(int i = 0; i < len; i++)
			{
				cout << "BOXES" << boxes_positions[i].x << " " << boxes_positions[i].y  << endl;
				/*if(boxes_positions[i].x == 6 && boxes_positions[i].y == 3){
				cout << "LÖSTE DE!" << endl;
				exit(0);
				}*/
			}
			cout << "================="<<endl;
		}


		/**
		 * Hash grejjer här nere grejja inte me
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
			hash += p.jens.x + p.jens.y;
			for(int i = 0; i < p.len; i++)
			{
				hash += p.boxes_positions[i].x + p.boxes_positions[i].y;
			}
			return hash;
		}

		int getLen(){
			return len;
		}
};
#endif
