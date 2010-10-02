/*
 * rules.cpp
 *
 *  Created on: 2 okt 2010
 *      Author: jacob
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


	//Get the lenght of the board. Which is the position of first '\n'.
	int width = boardIn.find("\n");
	// Height is then the total length of the string, divide with the height.
	int height = boardIn.length() / width;
	cout << "Height:\t" << height << endl << "Width:\t" << width << endl;

	// Koskenkorva.
	int x = 0, y = 0;


	Position jens;  // Jens is the man, this is his position. Will be in root.

	//Allocate memory for matrix, an iterates.
	while(iterator != boardIn.end())
	{
		if(*iterator == '\n')
		{
			// if newline add y (column)
			y++;
			x = 0;
		}
		else
		{
			Position p(x,y);
			switch (*iterator) {
				case BOX:
					boxes.push_back(p);
					this->set_floor(p);
					break;
				case JENS:
					jens = p;
					this->set_floor(p);
					break;
				case BOX_ONGOAL:
					boxes.push_back(p);
					this->add_goal(p);
					break;
				case JENS_ONGOAL:
					jens = p;
					this->add_goal(p);
					break;
				default:
					this->set(p, *iterator);
			}
			x++;
		}
		iterator++;
	}

	return true;
	//return Node(*jens,*jens,NULL,2);//Node(jens, jens, &boxes, &board);
}

