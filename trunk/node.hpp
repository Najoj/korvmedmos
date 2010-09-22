#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

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

public:
	Node();
	Node(Position p_current, Position p_prev,  vector <Position> *boxes,
		int ** board);
	
    // Destructor
	~Node();

	//Returns null if no child is available.
	Node getChild();


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



};
#endif
