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

Node::Node(Position jens, Node * parent, Position *boxes, int len, Position dir, int walker)
{
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

	path_cost = 0;
	if (parent != NULL) {
		parent->LAST_DIR = walker;
	}
}

/**
* Hash and hash related stuff. DO NOT TOUCH!
*/
bool Node::operator==(const Node & other) const
{
	if (this->jens != other.jens)
		return false;
	for (int i = 0; i < len; i++)
	{
		if (this->boxes_positions[i] != other.boxes_positions[i])
		return false;
	}
	return true;
}
size_t hash_value(Node const & p)
{
	std::size_t hash = 0;
	hash += 499973*p.jens.x + 849731*p.jens.y;
	for(int i = 0; i < p.len; i++)
	{
		hash += (612301*p.boxes_positions[i].x) & (1182463*p.boxes_positions[i].y);
	}
	return hash;
}

Position * Node::getBoxes()
{
	return boxes_positions;
}
int Node::getPathCost()
{
	return path_cost;
}
void Node::move_box(int i, Position p)
{
	boxes_positions[i] = p;
}
Position Node::getCurrent_position()
{
	return jens;
}
void Node::setCurrent_position(Position jens)
{
	this->jens = jens;
}
Node * Node::getParent()
{
	return parent;
}
int Node::getLen()
{
	return len;
}
