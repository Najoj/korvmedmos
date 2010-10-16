/*
 * back_rules.cpp
 *
 *  Created on: 14 okt 2010
 *      Author: jacob
 */

#include "back_rules.hpp"


bool BackRules::been_in_node(Node * node)
{

	NodeSet::iterator iterator = visited_nodes.find(*node);
	if (iterator != visited_nodes.end())
		return true;
	else
		return false;
}
Node * BackRules::youHasMe(Node * node)
{

	NodeSet::iterator iterator = visited_nodes.find(*node);
	if (iterator != visited_nodes.end())
		return new Node(*iterator);
	else
		return NULL;
}
bool BackRules::box_into_wall(){
	// Gets the prospective postion of the box.
	Position boxp = new_position_box.getDirection(w_dir);
//cout << "BOX_INTO WALL dir : " << moves_real[w_dir] << " POS: " << boxp.x << " " << boxp.y << endl;
	// Can not push a box into a wall.
	if(board->get(boxp) == WALL){
		//cout << "TROR ATT DET REDAN SITTER EN vagg  PÅ: " << boxp.x << " " << boxp.y << " dir" << moves_real[w_dir]<< endl;
		return false;
	}

	return true;
}
bool BackRules::box_into_deadlock(){
	// Gets the prospective postion of the box.
	Position boxp = new_position_box.getDirection(w_dir);

	// Can not push a box into a forbidden place.
	if(board->get(boxp) == BAD_POS){

		return false;
	}

	return true;
}
bool BackRules::box_into_box(){
	// Gets the prospective postion of the box.
	Position boxp = new_position_box.getDirection(w_dir);


	// Can not push a box into a box.
	if(board->get(boxp) == BOX || board->get(boxp) == BOX_ONGOAL){
//		cout << "TROR ATT DET REDAN SITTER EN BOX PÅ: " << boxp.x << " " << boxp.y << endl;
		return false;
	}
	return true;
}





bool BackRules::jens_into_box(){
	// Jens can not walk into a box.
	if(board->get(new_position) == BOX || board->get(new_position) == BOX_ONGOAL) {
		return true;
	}
	return false;
}
bool BackRules::jens_into_wall(){
	// Jens can not walk into a wall.
	if(board->get(new_position) == WALL){
		return true;
	}
	return false;
}

/**
* Reads the board into a int matrix called board (global var)
* @param string The String representing the board.
*/
bool BackRules::readBoard(std::string boardIn)
{
// Creates an iterator.
string::iterator iterator;
iterator = boardIn.begin();


// Get the lenght of the board. Which is the position of first '\n'.
int width = boardIn.find("\n");
// Height is then the total length of the string, divide with the height.
int height = boardIn.length() / width;
cout << "Height:\t" << height << endl << "Width:\t" << width << endl;

// Row and column counters.
int x = 0, y = 0;


// Create the board.
board = new Board(width,height);

if(board == NULL){
		cerr << "Failed to create board" << endl;
		exit(1);
}
// Allocate memory for matrix, an iterates.
while(iterator != boardIn.end())
{
		if(*iterator == '\n')
		{
				// If we got newline then add y.
				y++;
				x = 0;
		}
		else
		{
				Position p(x,y);
				switch (*iterator) {
						case BOX:

								board->add_goal(p);
								break;
						case JENS:
								board->setJens(p);
								board->set(p, FLOOR);
								break;
						case BOX_ONGOAL:
								board->boxes.push_back(p);
								board->add_goal(p);
								break;
						case JENS_ONGOAL:
								board->setJens(p);
								board->add_goal(p);
								break;
						case GOAL:

								board->boxes.push_back(p);
								board->set(p, FLOOR);
								break;
						default:
								board->set(p, *iterator);
				}
				x++;
		}
		iterator++;
	}

        return true;
}
Node * BackRules::getRootNode(){

	/**
	 * TODO: Make this nicer.
	 */
	//Temporarily copies boxes into a vector rather than stack!
	Position *temp_boxes = new Position[board->boxes.size()];
	for(unsigned short i = 0; i< board->boxes.size(); i++){
		temp_boxes[i] = board->boxes[i];
	}
	return new Node(*(board->getJens()),NULL,temp_boxes, board->boxes.size(),Position(-1,-1), 0);
}
/**
 * Prints the board with a give Node
 * TODO: TEST! This is basically copy paste from original main.cpp file.
 * TODO: Comment this SoB.
 */
void BackRules::printBoard(Node * node){
//	cout << endl << "JENS position: x" << (node->getCurrent_position().x) << " Y " << (node->getCurrent_position().y) << endl;
	for(int j = 0; j < board->height; j++)
	{
		for(int i = 0; i < board->width; i++)
		{
			if(node->getCurrent_position().x == i && node->getCurrent_position().y == j)
			{
				cout << JENS;
				continue;
			}
			cout << (unsigned char) board->get(i,j);
		}
		cout << endl;
	}
}

void BackRules::addBoxes()
{
	board->insert_boxes(node_in_process->getBoxes(),node_in_process->getLen());
}
//TODO: LOL @ Rishise :D CLASSIC JAKE HAX!!
void BackRules::removeBoxes()
{
        board->remove_boxes(node_in_process->getBoxes(),node_in_process->getLen());
       // node_in_process = NULL;
}


bool BackRules::solutionCheck(Node *n)
{
	// If every box is on the goal, then we hopefully have a valid solution.
	for(unsigned int i = 0; i < n->getLen(); i++)
	{
		if(board->get( n->getBoxes()[i] ) != GOAL)
		{
			return false;
		}

	}
	return true;
}



int BackRules::enforce(int dir){
	w_dir = dir;
	//CLASSIC JAKE HAXX!
	new_position = (node_in_process->getCurrent_position().getDirection(dir));

	//If jens is walking into a wall return fail.
	if(jens_into_wall()){
			return FAIL;
	}


	//Reverse the dir and checks if there is a box there, basically pull instead of push.
	new_position_box = (node_in_process->getCurrent_position().getDirection(revereseDir(dir)));
	//Is JENS walking into a box?
	if(jens_into_box()){
	//	cout << "JENS INTO BOX! aer en box pa: "  <<  (int)new_position.x << ","<< (int)new_position.y<<endl;
		return FAIL;
	}else{

		//see if we can push this box.
		// true är fail
		if( ! (box_into_wall() && box_into_box() /*&& box_into_deadlock()*/ /*&& box_into_boxlock()*/)){
		//	cout << "BOX INTO WALL ERL B INTO B FAIL" << endl;
			return FAIL;
		}

	}
    /**
  * TODO: Improve this plx
  */


	Position p(new_position.x, new_position.y);
	Node * n = new Node(p, node_in_process->getCurrent_position(),node_in_process, node_in_process->getBoxes(),node_in_process->getLen(), Position(0,0).getDirection(w_dir), dir);

	if(been_in_node(n))
	{
			delete n;

		 return FAIL;
	}
	delete n;

	cout << "return ok!" << endl;
	return OK;
}


