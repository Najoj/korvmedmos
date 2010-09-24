#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <boost/functional/hash.hpp>

#include "common.hpp"
using namespace std;

class Node{
private:
    // Position of player.
	Position p_current_position;
	
    // Previous position of player.
	Position p_prev_position;
    


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

	//Saves the latest direction
	short LAST_DIR;

	// Pointer to boxes positions.
	Position * boxes_positions;

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
    	cout << "================="<<endl;
    	cout << "JENS POS: " << p_current_position.x << " " << p_current_position.y << endl;
    	for(int i=0; i<len; i++){
    		cout << "BOXES" << boxes_positions[i].x << " " << boxes_positions[i].y  << endl;
    		/*if(boxes_positions[i].x == 6 && boxes_positions[i].y == 3){
    			cout << "LÖSTE DE!" << endl;
    			exit(0);
    		}*/
    	}

    	cout << "================="<<endl;
    }

    int sumBoxes(){
    	int ret = 0;
    	for(int i=0;i<len;i++){
    		ret += (boxes_positions[i].x)*17 * (boxes_positions[i].y)*29;
    	}

    	return ret;
    }
    friend std::size_t hash_value(Node const& p)
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, p.p_current_position.x);
            boost::hash_combine(seed, p.p_current_position.y);
            for(int i=0;i<p.len;i++){
            boost::hash_combine(seed, p.boxes_positions[i].x);
            boost::hash_combine(seed, p.boxes_positions[i].y);

            }
            return seed;
        }

};
#endif
