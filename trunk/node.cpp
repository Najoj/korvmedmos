#include "node.hpp"
#include "Board.hpp"

#include <ctime>
#include <cstdlib> 	// RANDOM

using namespace std;

Node::Node()
{
}

Node::Node(Position p_current, Position p_prev, vector<Position> *boxes,
Board * board)
{
	//Allocates array with positions.
	boxes_positions = new Position[boxes->size()];
	len = boxes->size();
	for(short j = 0; j < 4; j++)
	{
		used_directions[j] = 0;
	}
	
	// Uncommented
	for(unsigned int i = 0; i < boxes->size(); i++)
	{
		boxes_positions[i] = boxes->at(i);
	}
	
	//Saves positions.
	p_current_position = p_current;
	p_prev_position = p_prev;
	this->board = board;
}

/**
 * Create children
 */
Node::Node(Position p_current, Position p_prev, Position *boxes, Board * board, int len)
{
	this->len = len;
	//Allocates array with positions.
	boxes_positions = new Position[len];
	for(short j = 0; j<4; j++)
	{
		used_directions[j] = 0;
	}
	
	// Uncommented
	for(int i = 0; i < len; i++)
	{
		boxes_positions[i] = boxes[i];
	}
	//Saves positions.
	p_current_position = p_current;

	//cout << "Positionen e: " << p_current_position.x << " " << p_current_position.y << endl;
	p_prev_position = p_prev;
	this->board = board;
}

/**
 * Creat children (again)
 */
Node::Node(Position p_current, Position p_prev, Position *boxes, Board * board, int len, int movedBoxx, int movedBoxy)
{
	this->len = len;
	//Allocates array with positions.
	boxes_positions = new Position[len];

	//used_directions = {0,0,0,0}; // see header
	
	//
	for(short j = 0; j < 4; j++)
	{
		used_directions[j] = 0;
	}
	for(int i = 0; i < len; i++)
	{
		boxes_positions[i] = boxes[i];
		if (boxes_positions[i].x == p_current.x && boxes_positions[i].y == p_current.y)
		{
			boxes_positions[i].x = movedBoxx;
			boxes_positions[i].y = movedBoxy;
		}
	}

	//Saves positions.
	p_current_position = p_current;
	p_prev_position = p_current;
	this->board = board;
}

/**
 * DEAD LOCK HEAD SHOT, return true if locked position
 */
bool Node::deadlock(Position pos, Position parent)
{
	// Check left-right direction empty

	if ((board->get(pos.left()) == GOAL || board->get(pos.left()) == FLOOR ) && (board->get(pos.right()) == FLOOR || board->get(pos.right()) == GOAL )) {
		return false;
	}
	//Check up-right direction
	if ((board->get(pos.up()) == GOAL || board->get(pos.up()) == FLOOR ) && (board->get(pos.down()) == FLOOR || board->get(pos.down()) == GOAL )) {
			return false;
		}
	//if ( (board->get(pos.up()) != WALL || board->get(pos.up()) != BOX ) && (board->get(pos.down()) != WALL || board->get(pos.down()) != BOX ) ) {
//		return false;
//	}
//	if(pos.right() == parent || pos.left() == parent ){
	//	return false;
//	}
	if (board->get(pos.right()) == BOX || board->get(pos.left()) == BOX ) {

		if(pos.right() == parent){
			return deadlock(pos.left(),pos);
		}

		else if(pos.left() == parent){
			return deadlock(pos.right(),pos);
		}

		else{
			return deadlock(pos.right(),pos) || deadlock(pos.left(),pos);
		}
	}

	if (board->get(pos.up()) == BOX || board->get(pos.down()) == BOX ) {
		if(pos.up() == parent){
			return deadlock(pos.down(),pos);
		}else if(pos.down() == parent){
			return deadlock(pos.up(),pos);
		}else{
			return deadlock(pos.down(),pos) || deadlock(pos.up(),pos);
		}
	}

	cout << "DEAD LOCK!!!" << endl;
	return true;
}

/**
 * Return NULL if no children found, otherwise, return the child
 */
Node  * Node::getChildDirection(int dir)
{
	int xdir = 0, ydir = 0;
	if(dir == UP)
		ydir = -1;
	else if(dir == RIGHT)
		xdir = 1;
	else if(dir == DOWN)
		ydir = 1;
	else // dir == LEFT
		xdir = -1;
	
	// Check if Jens goes in to wall, if already tested direction, if previous position
	if (board->get(p_current_position.x+xdir, p_current_position.y+ydir) == WALL || used_directions[dir] == USED
	|| (p_prev_position.x == (p_current_position.x+xdir) && p_prev_position.y == (p_current_position.y+ydir)))
	{
		//Avoids repeating this action
		used_directions[dir] = USED;
		return NULL;
	}
	else
	{
		//Check if there is a box
		for (int i = 0; i<len; i++)
		{
			// Check if it as box in front.
			if (boxes_positions[i].x == p_current_position.x+xdir && boxes_positions[i].y == p_current_position.y+ydir)
			{
				//Position beyondbox(p_current_position.x+xdir*2, p_current_position.y+ydir*2);
				// If there is a wall on the other side of the box
				if (board->get(p_current_position.x+xdir+xdir, p_current_position.y+ydir+ydir) == WALL)
				{
					return NULL;
				}

				// If moving box to corner column and there is no goal there (then it's stuck)
				if (!board->xline_has_goal(p_current_position.x+xdir+xdir))
				{
					if (p_current_position.x+xdir+xdir == 1 || p_current_position.x+xdir+xdir == board->width-2)
						return NULL;
				}
				// If moving box to corner row and there is no goal there (then it's stuck)
				if (!board->yline_has_goal(p_current_position.y+ydir+ydir))
				{
					if (p_current_position.y+ydir+ydir == 1 || p_current_position.y+ydir+ydir == board->height-2){

						return NULL;
					}
				}

				if(deadlock( Position(p_current_position.x+xdir*2, p_current_position.y+ydir*2 ), Position(p_current_position.x+xdir*2, p_current_position.y+ydir*2 ) ) ){
					return NULL;
				}
				// If box would go to corner that is not goal
				/*if (board->get(p_current_position.x+xdir+xdir, p_current_position.y+ydir+ydir) != GOAL)
				{
					// UP-DOWN
					if (board->get(p_current_position.x+xdir*3, p_current_position.y+ydir*3) == WALL &&
					(board->get(p_current_position.x+1, p_current_position.y+ydir*2) == WALL ||
					board->get(p_current_position.x-1, p_current_position.y+ydir*2) == WALL))
					{
						cout << "If box would go to corner that is not goal:UP-DOWN" << endl;
						return NULL;
					}
					
					// LEFT-RIGHT
					if (board->get(p_current_position.x+xdir*3, p_current_position.y+ydir*3) == WALL &&
					(board->get(p_current_position.x+xdir*2, p_current_position.y+1) == WALL ||
					board->get(p_current_position.x+xdir*2, p_current_position.y-1) == WALL))
					{
						cout << "If box would go to corner that is not goal:LEFT-RIGHT" << endl;
						return NULL;
					}
				}*/

				// Check if there is box on other side of box
				for (int j=0; j<len; j++)
				{
					if (boxes_positions[j].x == p_current_position.x+xdir+xdir && boxes_positions[j].y == p_current_position.y+ydir+ydir)
					{
						return NULL;
					}
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

Node  * Node::getChild()
{

//* SUGGESTION ON RANDOM WALK

	bool check[] = {0, 0, 0, 0};
	int random = USED;
	Node * ret = NULL;
	// Seed
	srand(4711);
	do
	{
		random = rand() % 4;
//		cout << random << endl;	// Print the random numbers.
		ret = getChildDirection( random );
		check[random] = 1;
	} while( ret == NULL && ! (check[UP] && check[RIGHT] && check[DOWN] && check[LEFT]));
	
	return ret;

//*/

/*
	// Go through every movment we can do.
//	Node  * ret = getChildDirection(UP, 0, -1);		// Get UP
	Node  * ret = getChildDirection(UP);		// Get UP
	if (ret == NULL)
	{
//		ret = getChildDirection(RIGHT, 1, 0);		// Get RIGHT
		ret = getChildDirection(RIGHT);		// Get RIGHT
	}
	if (ret == NULL)
	{
//		ret = getChildDirection(DOWN, 0, 1);		// Get DOWN
		ret = getChildDirection(DOWN);		// Get DOWN
	}
	if (ret == NULL)
	{
//		ret = getChildDirection(LEFT, -1, 0);		// Get LEFT
		ret = getChildDirection(LEFT);			// Get LEFT
	}
// */


/*	// Shorter version of the above code. Not the random walk.
	Node * ret = getChildDirection(0);	// UP
	// RIGHT, DOWN, LEFT
	for(int i = 1; i < 4 ; i++)
	{
		if (ret != NULL)
			break;
		ret = getChildDirection(i);
	}
//*/
	return ret;
}
