#include "node.hpp"

Node::Node(){

}

Node::Node(Position p_current, Position p_prev, vector<Position> *boxes,
		int ** board){
	//Allocates array with positions.
	boxes_positions = new Position[boxes->size()];
	len = boxes->size();
	for(short j = 0; j<4; j++){
		used_directions[j] = 0;
	}
	//
	for(unsigned int i = 0; i < boxes->size(); i++){
		boxes_positions[i] = boxes->at(i);
	}

	// Johan > Jacob

	//Saves positions.
	p_current_position = p_current;
	p_prev_position = p_prev;
	this->board = board;
}
/**
 * Göra barn
 */
Node::Node(Position p_current, Position p_prev, Position *boxes, int ** board, int len){

	this->len = len;
	//Allocates array with positions.
	boxes_positions = new Position[len];
	for(short j = 0; j<4; j++){
		used_directions[j] = 0;
	}
	//
	for(int i = 0; i < len; i++){
		boxes_positions[i] = boxes[i];
	}

	//Saves positions.
	p_current_position = p_current;

	//cout << "Positionen e: " << p_current_position.x << " " << p_current_position.y << endl;
	p_prev_position = p_prev;
	this->board = board;
}

/**
 * Göra barn
 */
Node::Node(Position p_current, Position p_prev, Position *boxes, int ** board, int len, int movedBoxx, int movedBoxy){

	this->len = len;
	//Allocates array with positions.
	boxes_positions = new Position[len];
	//used_directions = {0,0,0,0}; see header
	//
	for(short j = 0; j<4; j++){
		used_directions[j] = 0;
	}
	for(int i = 0; i < len; i++){
		boxes_positions[i] = boxes[i];
		if (boxes_positions[i].x == p_current.x && boxes_positions[i].y == p_current.y){
			boxes_positions[i].x = movedBoxx;
			boxes_positions[i].y = movedBoxy;
		}
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


Node  * Node::getChildDirection(int dir, int xdir, int ydir)
{

	//
	if (board[p_current_position.x+xdir][p_current_position.y+ydir] == WALL || used_directions[dir] == USED
			|| (p_prev_position.x == (p_current_position.x+xdir) && p_prev_position.y == (p_current_position.y+ydir))) {
		//Avoids repeating this action

		used_directions[dir] = USED;
		return NULL;
	} else {
		//Check if there is a box
		for (int i = 0; i<len; i++)
		{
			// kolla om de e låda
			if (boxes_positions[i].x == p_current_position.x+xdir && boxes_positions[i].y == p_current_position.y+ydir) {

				// If there is a wall to the right of the box to jensus right
				if (board[p_current_position.x+xdir+xdir][p_current_position.y+ydir+ydir] == WALL){
					return NULL;
				}
				//Makes sure we never go this way again from this node.
				used_directions[dir] = USED;

				//Saves the last
				LAST_DIR = dir;

				return new Node(boxes_positions[i], p_current_position, boxes_positions, board, len, p_current_position.x+xdir+xdir, p_current_position.y+ydir+ydir);
			}
		}
		Position newp;
		newp.x = p_current_position.x+xdir;
		newp.y = p_current_position.y+ydir;
		//Makes sure we never go this way again from this node.
		used_directions[dir] = USED;

		//Saves the last
		LAST_DIR = dir;

		return new Node(newp, p_current_position, boxes_positions, board, len);

	//	Node child = Node(newPos, p_current_position,
	}
	return NULL;
}

Node  * Node::getChild(){
	//go trough every movment we can do.
	Node  * ret = getChildDirection(UP, 0, -1);
	if (ret == NULL){

		ret = getChildDirection(RIGHT, 1, 0);
	}
	if (ret == NULL){

		ret = getChildDirection(DOWN, 0, 1);
	}
	if (ret == NULL)
		ret = getChildDirection(LEFT, -1, 0);
	return ret;
}

