#include "node.hpp"

Node::Node(){

}

Node::Node(Position p_current, Position p_prev, vector<Position> *boxes,
		int ** board){
	//Allocates array with positions.
	boxes_positions = new Position[boxes.size()];
	used_directions = {0,0,0,0};
	//
	for(int i = 0; i < boxes.size(); i++){
		boxes_positions[i] = boxes->at(i);
	}

	//Saves positions.
	p_current_position = p_current;
	p_prev_position = p_prev;
	this->board = board;
}

//Do cleanup.
Node::~Node(){

}

/**
 * Return NULL if no children found, otherwise, return the child
 */
Node Node::getChildren(){
	if (board[p_current_position.x+1, p_current_position.y] == WALL) {
		used_directions[RIGHT] = -1;
		Position newPos;
		newPos.x = p_current_position.x+1;
		newPos.y = p_current_position.y;
		for (int i = 0; boxes_positions.size(); i++)
		{
			if (boxes_positions[i].x == newPos.x &&
					boxes_positions[i].y == newPos.y) {
				boxes_positions[i]
			}
		}
		Node child = Node(newPos, p_current_position, 
	}
	if (board[p_current_position.x-1, p_current_position.y] == WALL) {
		used_directions[LEFT] = -1;
	}
	if (board[p_current_position.x, p_current_position.y+1] == WALL) {
		used_directions[DOWN] = -1;
	}
	if (board[p_current_position.x, p_current_position.y-1] == WALL) {
		used_directions[UP] = -1;
	}

	for (int i=0; i<4; i++)
	{
		if (used_directions[i] != -1)
			
	} 
	
	board[p_current_position.x-1, p_current_position.y]
	
	board[p_current_position.x, p_current_position.y+1]
	
	board[p_current_position.x, p_current_position.y-1]
	
	return NULL;
}

