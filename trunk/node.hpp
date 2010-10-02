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
		Position p_current_position;
		
		// Previous position of player.
		Position p_prev_position;
		short used_directions[4];
		
		Board * board;

		Node  * getChildDirection(int dir/*, int xdir, int ydir*/);

		bool deadlock(Position pos, Position parent);
	public:
		Node();
		Node(Position p_current, Position p_prev,  vector <Position> *boxes,
		Board * board);
		Node(Position p_current, Position p_prev, Position *boxes, Board * board, int len);
		Node(Position p_current, Position p_prev, Position *boxes, Board * board, int len, int movedBoxx, int movedBoxy);

		//Returns null if no child is available.
		Node  * getChild();



		//Saves the latest direction
		short LAST_DIR;
		int len;
		// Pointer to boxes positions.
		Position * boxes_positions;

		/**
		* Auto genereated getter and setter methods.
		*/
		Position * getBoxes()
		{
			return boxes_positions;
		}
		
		Position getCurrent_position() const
		{
			return p_current_position;
		}
		
		Position getPrev_position() const
		{
			return p_prev_position;
		}
		
		void setCurrent_position(Position p_current_position)
		{
			this->p_current_position = p_current_position;
		}
		
		void setPrev_position(Position p_prev_position)
		{
			this->p_prev_position = p_prev_position;
		}
		
		void print()
		{
			cout << "================="<<endl;
			cout << "JENS POS: " << p_current_position.x << " " << p_current_position.y << endl;
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

		int sumBoxes()
		{
			int ret = 0;
			for(int i=0; i < len; i++)
			{
				ret += (boxes_positions[i].x)*17 * (boxes_positions[i].y)*29;
			}
			return ret;
		}

		bool operator==(const Node & other) const
		{
			if (this->p_current_position != other.p_current_position)
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
			hash += p.p_current_position.x + p.p_current_position.y;
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
