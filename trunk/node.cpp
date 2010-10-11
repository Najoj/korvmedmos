/**
 * node.cpp
 * 
 * We need this in the tree of all possible directions to that we use in our
 * search for a Sokokban board solution.
 */
#include <ctime>
#include <cstdlib> 	// Used for random.

#include "node.hpp"
#include "Board.hpp"

using namespace std;

Node::Node()
{
}
Node::Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walker) {

	this->len = len;
	boxes_positions = new Position[len];
	// Copy boxes.
	for(int i = 0; i < len; i++)
	{
		// Update boxes if needed.
		if(boxes[i].x == jens.x && boxes[i].y == jens.y) {
		//	cout << "Uppdaterar boxar!";
			boxes_positions[i].x = boxes[i].x + dir.x;
			boxes_positions[i].y = boxes[i].y + dir.y;
		} else {
			boxes_positions[i] = boxes[i];
		}
	}

	// Saves Jens' posistion.
	this->jens = jens;
	// Sets parent node
	this->parent = parent;

	path_cost = 4711;

	if (parent != NULL) {
		parent->LAST_DIR = walker;
	}
}

