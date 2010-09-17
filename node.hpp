#ifndef NODE_HPP
#define NODE_HPP

#include "common.hpp"

class Node{
private:
	Position p_current_position;

	Position p_prev_position;

	Position boxes_positions[];

public:
	Node();
	Node(int len);

	~Node();



	/**
	 * Auto genereated getter and setter methods.
	 */
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
