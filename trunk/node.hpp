#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "common.hpp"
using namespace std;

class Node{
private:
    // Position of player.
	Position p_current_position;
	
    // Previous position of player.
	Position p_prev_position;
    
    // Pointer to boxes positions.
	Position * boxes_positions;

	short used_directions[4];

	int ** board;

	int len;


	Node  * getChildDirection(int dir, int xdir, int ydir);

public:
	Node();
	Node(Position p_current, Position p_prev,  vector <Position> *boxes,
		int ** board);
	Node(Position p_current, Position p_prev, Position *boxes,int ** board, int len);
	Node(Position p_current, Position p_prev, Position *boxes, int ** board, int len, int movedBoxx, int movedBoxy);
    // Destructor
	~Node();

	//Returns null if no child is available.
	Node  * getChild();



	/**
	 * Auto genereated getter and setter methods.
	 */
	Position * getBoxes(){
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


    void print(){
    	cout << "EN MAMMA BRÄDA" << endl;
    	for(unsigned int i=0; i<len; i++){
    		cout << "BOXES" << boxes_positions[i].x << " " << boxes_positions[i].x  << endl;
    	}

    	cout << "================="<<endl;
    }

};
#endif
