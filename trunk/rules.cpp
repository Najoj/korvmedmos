/**
 * rules.cpp
 *
 * Keeps the fundamental, basic rules of the Sokoban game play.
 */

#include "rules.hpp"

bool Rules::been_in_node(Node * node)
{

	NodeSet::iterator iterator = visited_nodes.find(*node);
	if (iterator != visited_nodes.end())
		return true;
	else
		return false;
}

/**
* Reads the board into a int matrix called board (global var)
* @param string The String representing the board.
*/
bool Rules::readBoard(std::string boardIn)
{
	// Creates an iterator.
	string::iterator iterator;
	iterator = boardIn.begin();


	// Get the lenght of the board. Which is the position of first '\n'.
	int width = boardIn.find("\n");
	// Height is then the total length of the string, divide with the height.
	int height = boardIn.length() / width;
	cout << "Height:\t" << height << endl << "Width:\t" << width << endl;

	// Koskenkorva.
	int x = 0, y = 0;


	// Create the board.
	board = new Board(width,height);

	if(board == NULL) {
		cerr << "FAILED" << endl;
	}
	// Allocate memory for matrix, an iterates.
	while(iterator != boardIn.end())
	{
		if(*iterator == '\n')
		{
			// If iterator is a newline, then we add y and reset x.
			y++;
			x = 0;
		}
		else
		{
			Position p(x,y);
			switch (*iterator) {
				case BOX:
					board->boxes.push_back(p);
					board->set_floor(p);
					break;
				case JENS:
					board->setJens(p);
					board->set_floor(p);
					break;
				case BOX_ONGOAL:
					board->boxes.push_back(p);
					board->add_goal(p);
					break;
				case JENS_ONGOAL:
					board->setJens(p);
					board->add_goal(p);
					break;
				default:
					board->set(p, *iterator);
			}
			x++;
		}
		iterator++;
	}

	return true;
	//return Node(*jens,*jens,NULL,2);//Node(jens, jens, &boxes, &board);
}

Node Rules::getRootNode() {

	/**
	 * TODO: Make this nicer.
	 */
	// Temporarily copies boxes into a vector rather than stack.
	Position *temp_boxes = new Position[board->boxes.size()];
	for(unsigned short i = 0; i< board->boxes.size(); i++) {
		temp_boxes[i] = board->boxes[i];
	}
	return Node(*(board->getJens()),NULL,temp_boxes, board->boxes.size(),Position(-1,-1));
}
/**
 * Prints the board with a give Node
 * TODO: Test this. This is basically copy-paste from original main.cpp file.
 */
void Rules::printBoard(Node * node) {
bool found = false;
	cout << endl << "JENS position: x" << (node->getCurrent_position().x) << " Y " << (node->getCurrent_position().y) << endl;
	for(int j = 0; j < board->height; j++)
	{
		for(int i = 0; i < board->width; i++)
		{
			if(node->getCurrent_position().x == i && node->getCurrent_position().y == j)
			{
				cout << JENS;
				continue;
			}
			found = false;
			for(int k = 0; k < node->getLen(); k++)
			{
				if(node->getBoxes()[k].x == i && node->getBoxes()[k].y == j)
				{
					if (board->get(node->getBoxes()[k]) == GOAL)
						cout << BOX_ONGOAL;
					else
						cout << BOX;
					
					found = true;
					break;
				}
			}
			if(!found)
			{
				cout << (unsigned char) board->get(i,j) << "";
			}
		}
		cout << endl;
	}
}

