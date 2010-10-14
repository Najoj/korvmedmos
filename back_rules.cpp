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
bool BackRules::box_into_wall(){
	// Gets the prospective postion of the box.
	Position boxp = op_new_position.getDirection(w_dir);
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
	Position boxp = op_new_position.getDirection(w_dir);

	// Can not push a box into a forbidden place.
	if(board->get(boxp) == BAD_POS){

		return false;
	}

	return true;
}
bool BackRules::box_into_box(){
	// Gets the prospective postion of the box.
	Position boxp = op_new_position.getDirection(w_dir);


	// Can not push a box into a box.
	if(board->get(boxp) == BOX || board->get(boxp) == BOX_ONGOAL){
//		cout << "TROR ATT DET REDAN SITTER EN BOX PÅ: " << boxp.x << " " << boxp.y << endl;
		return false;
	}
	return true;
}
/*
void print_matrix(int matrix[3][3])
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (matrix[i][j] == 0) cout << " ";
			else cout << (char)matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}*/

/*int matrix_hash(int matrix[3][3])
{
	int hash = 0;
	for (int i = 0; i < 9; i++)
	{
		hash += (int*)matrix[i]
}*/

/*
 * return true if boxlock was not found
 *//*
bool find_boxlock(int matrix[3][3])
{
	bool equal = true;
	for (int i = 0; i < NUMBER_OF_LOCKS; i++)
	{
		equal = true;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (boxlocks[i][j][k] == 0)
					continue;
				if (matrix[j][k] != boxlocks[i][j][k])
					equal = false;
			}
		}
		if (equal) {
			return true;
		}
	}
	return false;
}
*/
/*
bool BackRules::box_into_boxlock()
{
	int matrix[3][3];

	// Gets the prospective postion of the box.
	Position boxp = new_position.getDirection(w_dir);
	int oldbox = board->get(new_position);
	board->set(new_position, FLOOR);

	matrix[0][0] = board->get(boxp.left().up());
	matrix[1][0] = board->get(boxp.up());
	matrix[2][0] = board->get(boxp.up().right());
	matrix[0][1] = board->get(boxp.left());
	matrix[1][1] = (board->get(boxp) == GOAL) ? BOX_ONGOAL : BOX;
	matrix[2][1] = board->get(boxp.right());
	matrix[0][2] = board->get(boxp.down().left());
	matrix[1][2] = board->get(boxp.down());
	matrix[2][2] = board->get(boxp.down().right());

	bool boxes_on_goal = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matrix[i][j] == BOX)
				boxes_on_goal = false;
			if (matrix[i][j] == BOX_ONGOAL)
				matrix[i][j] = BOX;
			else if (matrix[i][j] == BAD_POS)
				matrix[i][j] = 0;
			else if (matrix[i][j] == FLOOR)
				matrix[i][j] = 0;
			else if (matrix[i][j] == GOAL) {
				matrix[i][j] = 0;
			}
		}
	}
	board->set(new_position, oldbox); // reset box position

	if (boxes_on_goal)
		return true;
	else
		return !find_boxlock(matrix); // om vi är i ett boxlock, returnerar find_boxlock true, då är det fail, då returnar vi false
}*/

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

Node BackRules::getRootNode(){


	/**
	 * TODO: Make this nicer.
	 */
	//Temporarily copies boxes into a vector rather than stack!
	Position *temp_boxes = new Position[board->boxes.size()];
	for(unsigned short i = 0; i< board->boxes.size(); i++){
		temp_boxes[i] = board->boxes[i];
	}
	return Node(*(board->getJens()),NULL,temp_boxes, board->boxes.size(),Position(-1,-1), 0);
}
/**
 * Prints the board with a give Node
 * TODO: TEST! This is basically copy paste from original main.cpp file.
 * TODO: Comment this SoB.
 */
void BackRules::printBoard(Node * node){
	bool found = false;
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

bool BackRules::solutionCheck(Node *n)
{
	// If every box is on the goal, then we hopefully have a valid solution.
	for(unsigned int i = 0; i < board->goals.size(); i++)
	{
		if(board->get( board->goals[i] ) != BOX_ONGOAL)
		{
			return false;
		}

	}
	return true;
}

int BackRules::length_from_jens_to_box(int dir, Node * parent)
	{
		int cost = 0;

		Position new_jens = parent->getCurrent_position();

		int min = BIG_VALUE;
		int min_i = 0; // i-värdet för minsta boxen
		int save;
		if(dir == UP)
		{
			new_jens.y--;
		}
		else if(dir == RIGHT)
		{
			new_jens.x++;
		}
		else if(dir == DOWN)
		{
			new_jens.y++;
		}
		else // (dir == LEFT)
		{
			new_jens.x--;
		}

		for(int i = 0; i < parent->getLen(); i++)
		{
			save = Heuristics::length_to_box(new_jens, parent->getBoxes()[i]);
			if(save < min)
			{
				min = save;
				min_i = i;
			}
		}
		cost += min;
		if (board->get(parent->getBoxes()[min_i]) == GOAL) {
			cost += 5;
		}

		return cost;
	}

int BackRules::jens_box_goal_distance(int dir)
	{
		//bool debug = false;
		//int debug_nr = 0;
		int min = BIG_VALUE, save, push_box_dir = NO_DIR;
		Position nearest_box, nearest_goal;
		Position temp;
		int jens_to_push_box_dir, box_to_goal_distance;
		int cost = 0;

		Position new_jens = getXYDir(dir, node_in_process->getCurrent_position());

		if(board->get(new_jens) == BOX_ONGOAL){
			cost += COST_TO_MOVE_BOX_ON_GOAL;
		}

		// Find nearest box from Jens
		for(int i = 0; i < node_in_process->getLen(); i++)
		{
			temp = node_in_process->getBoxes()[i];
			save = Heuristics::length_to_box(new_jens, temp);

			if(board->get(temp) != BOX_ONGOAL && save < min)
			{
				min = save;
				nearest_box = temp;
			}
		}

//		cout << "Chosen box: " << (int) nearest_box.x << " " << (int) nearest_box.y << endl;

		// Reset min
		min = BIG_VALUE;
		// Find nearest goal from nearest box
		for(int i = 0; i < node_in_process->getLen(); i++)
		{
			temp = board->goals[i];
			save = Heuristics::length_to_box(nearest_box, temp);

			if(board->get(temp) != BOX_ONGOAL && save < min)
			{
				min = save;
				nearest_goal = temp;
			}
		}
//		cout << "Chosen goal: " << (int) nearest_goal.x << " " << (int) nearest_goal.y << endl;

		box_to_goal_distance = min;
		if( abs(nearest_goal.x - nearest_box.x) < abs(nearest_goal.y - nearest_box.y)
			&& abs(nearest_goal.x - nearest_box.x) != 0 )
		{

			if( nearest_goal.x - nearest_box.x > 0 )
				push_box_dir = RIGHT;
			else // nearest_goal.x - nearest_box.x <= 0
				push_box_dir = LEFT;

		}
		else if( abs(nearest_goal.x - nearest_box.x) >= abs(nearest_goal.y - nearest_box.y)
				|| abs(nearest_goal.x - nearest_box.x) == 0 )
		{
			if( nearest_goal.y - nearest_box.y > 0 )
				push_box_dir = DOWN;
			else // nearest_goal.y - nearest_box.y <= 0
				push_box_dir = UP;
		}
		else
		{
			cout << "WUT THE FUKK" << endl;
		}

		if(push_box_dir == RIGHT)
			temp = nearest_box.getDirection(LEFT);
		else if(push_box_dir == LEFT)
			temp = nearest_box.getDirection(RIGHT);
		else if(push_box_dir == UP)
			temp = nearest_box.getDirection(DOWN);
		else if(push_box_dir == DOWN)
			temp = nearest_box.getDirection(UP);

//		cout << "Direction: " << moves_real[push_box_dir] << endl;
		if (node_in_process->getCurrent_position() == temp && push_box_dir == dir) {
			cost = 0;
		} else {
			jens_to_push_box_dir = Heuristics::length_to_box(new_jens, temp);
			cost += jens_to_push_box_dir;
		}

		cost += box_to_goal_distance;

		return cost;
	}
int BackRules::enforce(int dir){
	w_dir = dir;
	//CLASSIC JAKE HAXX!
	new_position = (node_in_process->getCurrent_position().getDirection(dir));
	op_new_position =(node_in_process->getCurrent_position().getDirection(revereseDir(dir)));
	//If jens is walking into a wall return fail.
	if(jens_into_wall()){
			return FAIL;
	}

	//Jens cannot walk into a box
	if(jens_into_box()){
		return FAIL;
	}
	int moved = -1;

		//see if we can push this box.
		// true är fail
	if( ! (box_into_wall() && box_into_box() /*&& box_into_deadlock()*/ /*&& box_into_boxlock()*/)){
		cout << "De va jag som faila " << endl;
				return FAIL;
	}
		for(int i = 0; i < node_in_process->getLen(); i++)
		{
			// Update box.
			if(node_in_process->getBoxes()[i] == op_new_position) {
				node_in_process->move_box(i, op_new_position+Position(0,0).getDirection(w_dir));
				moved = i;
				break;
			}

	}
		//Saves jens old position for some reason?
	Position oldjens = node_in_process->getCurrent_position();
	//Updates jens position but why?
	node_in_process->setCurrent_position(new_position);
	bool visited = been_in_node(node_in_process);
	if (moved != -1)
		node_in_process->move_box(moved, op_new_position);
		node_in_process->setCurrent_position(oldjens);

	if(visited)
		return FAIL;
	return OK;
}

int BackRules::heuristics(int dir){
	int cost = 0;

	cost += jens_box_goal_distance(dir);

	return cost;
}
