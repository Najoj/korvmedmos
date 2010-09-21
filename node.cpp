#include "node.hpp"

Node::Node(){

}

Node::Node(int len, Position p_current, Position p_prev, vector<Position> *boxes){
	//Allocates array with positions.
	boxes_positions = new Position[len];

	//
	for(int i = 0; i<len; i++){
		boxes_positions[i] = boxes->at(i);
	}

	//Saves positions.
	p_current_position = p_current;
	p_prev_position = p_prev;
}

//Do cleanup.
Node::~Node(){

}

/**
 * Return NULL if no children found, otherwise, return the child
 */
Node Node::getChildren(){

	return NULL;
}

