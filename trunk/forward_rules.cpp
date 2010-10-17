/*
 * rules.cpp
 *
 *  Created on: 2 okt 2010
 *      Author: jacob
 *
 *
 *   Enforces rules for the forward search
 */

#include "forward_rules.hpp"
#include "boxlocks.hpp"

bool ForwardRules::been_in_node(Node * node)
{

	NodeSet::iterator iterator = visited_nodes.find(*node);
	if (iterator != visited_nodes.end())
		return true;
	else
		return false;
}
/**
 * Checks if this hashet contains given node, returns the node or null
 */
Node * ForwardRules::youHasMe(Node * node)
{

	NodeSet::iterator iterator = visited_nodes.find(*node);
	if (iterator != visited_nodes.end())
		return new Node(*iterator);
	else
		return NULL;
}
/**
 * Checks if we try to push box into a wall
 */
bool ForwardRules::box_into_wall(){
	// Gets the prospective postion of the box.
	Position boxp = new_position.getDirection(w_dir);

	// Can not push a box into a wall.
	if(board->get(boxp) == WALL){
		return false;
	}

	return true;
}
/**
 * Avoids deadlocks ie. pushing a box onto a x
 */
bool ForwardRules::box_into_deadlock(){
	// Gets the prospective postion of the box.
	Position boxp = new_position.getDirection(w_dir);

	// Can not push a box into a forbidden place.
	if(board->get(boxp) == BAD_POS){

		return false;
	}

	return true;
}
bool ForwardRules::box_into_box(){
	// Gets the prospective postion of the box.
	Position boxp = new_position.getDirection(w_dir);


	// Can not push a box into a box.
	if(board->get(boxp) == BOX || board->get(boxp) == BOX_ONGOAL){
		return false;
	}
	return true;
}




/*
 * 	See boxlocks.hpp for the definitions of the boxlocks matrix
 * return true if boxlock was not found
 */
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
/**
 * Stops box locks.
 */
bool ForwardRules::box_into_boxlock()
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
}

bool ForwardRules::jens_into_box(){
	// Jens can not walk into a box.
	if(board->get(new_position) == BOX || board->get(new_position) == BOX_ONGOAL) {
		return true;
	}
	return false;
}
bool ForwardRules::jens_into_wall(){
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
bool ForwardRules::readBoard(std::string boardIn)
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
					board->boxes.push_back(p);
					board->set(p, FLOOR);
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
}

/**
 * Returns the root node, the "starting state of the world"
 */
Node * ForwardRules::getRootNode(){


	//Temporarily copies boxes into a vector rather than stack!
	Position *temp_boxes = new Position[board->boxes.size()];
	for(unsigned short i = 0; i< board->boxes.size(); i++){
		temp_boxes[i] = board->boxes[i];
	}
	return new Node(*(board->getJens()),NULL,temp_boxes, board->boxes.size(),Position(-1,-1), 0);
}
/**
 * Prints the board with a give Node
 */
void ForwardRules::printBoard(Node * node){
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

void ForwardRules::addBoxes()
{
	board->insert_boxes(node_in_process->getBoxes(),node_in_process->getLen());
}
//LOL @ Rishise :D CLASSIC JAKE HAX!!
void ForwardRules::removeBoxes()
{
        board->remove_boxes(node_in_process->getBoxes(),node_in_process->getLen());
       // node_in_process = NULL;
}


bool ForwardRules::solutionCheck(Node *n)
{
	// If every box is on the goal, then we hopefully have a valid solution.
	for(int i = 0; i < n->getLen(); i++)
	{
		if(board->get( n->getBoxes()[i] ) != GOAL)
		{
			return false;
		}

	}
	return true;
}



/**
 * Return the cost to get the nearest box to goal
 */
int ForwardRules::box_goal_distance(Node * parent, Position &jens){


                int save = BIG_VALUE;
                int min_jens_to_box = BIG_VALUE;
                int min_box_to_goal = BIG_VALUE;

                Position nearest_box, nearest_goal;
                Position temp;

                int cost = 0;

                Position new_jens = jens;

                //Finds out which box is closest to jens
                for(int i = 0; i < parent->getLen(); i++)
                {

                        temp = parent->getBoxes()[i];
                        if(board->get(temp) == BOX){
                                save = length_to_box(new_jens, temp);
                                if(board->get(temp) != BOX_ONGOAL && save < min_jens_to_box)
                                {
                                        min_jens_to_box = save;
                                        nearest_box = temp;
                                }
                        }else if(board->get(temp) == BOX_ONGOAL){
                                //cout << (int)temp.x << "," << (int)temp.y << " has a box on a goal." << endl;

                        }
                }


                //Finds the shortest path for the selected box to goal
                for(int i = 0; i < parent->getLen(); i++)
                {
                        temp = board->goals[i];
                        if(board->get(temp) == GOAL){
                                save = length_to_box(nearest_box, temp);
                                if(board->get(temp) != BOX_ONGOAL && save < min_box_to_goal)
                                {
                                        min_box_to_goal = save;
                                        nearest_goal = temp;
                                        //cout << "len to goal" << min_box_to_goal << endl;
                                }
                        }else{
                                //cout << (int)temp.x << "," << (int)temp.y << " has no goal." << endl;

                        }
                }

                if(min_box_to_goal == 0 || min_box_to_goal == BIG_VALUE){
                        return 0;
                }

                cost = min_box_to_goal + min_jens_to_box;


                //Removes the boxes and goal positions
                board->set(nearest_box,WALL);
                board->set(nearest_goal, WALL);

                jens = nearest_goal;


                return cost;
        }
/*
 * Enforces the basic rules of the game and also some deadlock prevention
 * return FAIL if we cannto go in this direction, the node beeing tested is set by
 * node_in_process.
 */
int ForwardRules::enforce(int dir){
	w_dir = dir;
	//CLASSIC JAKE HAXX!
	new_position = (node_in_process->getCurrent_position().getDirection(dir));

	//If jens is walking into a wall return fail.
	if(jens_into_wall()){
			return FAIL;
	}
	bool jens_next_box = false;
	//Is JENS walking into a box?
	if(jens_into_box()){
		jens_next_box = true;
		//see if we can push this box.
		// true är fail
		if( ! (box_into_wall() && box_into_box() && box_into_deadlock() && box_into_boxlock())){
				return FAIL;
		}

	}
    /**
  * TODO: Improve this plx
  */

	//Checks the hashset if we have already visited this state
	Position p(new_position.x, new_position.y);
	Node * n = new Node(p, node_in_process,node_in_process->getBoxes(),node_in_process->getLen(), Position(0,0).getDirection(w_dir), dir);

	if(been_in_node(n))
	{
			delete n;

		 return FAIL;
	}
	delete n;
	return OK;
}


/**
 * Pythagoras distance calc between two positions in the board.
 */
int ForwardRules::length_to_box(Position jens, Position box)
		{
			return abs(jens.x - box.x) + abs(jens.y - box.y);
//			return sqrt((jens.x - box.x)*(jens.x - box.x) + (jens.y-box.y)*(jens.y-box.y));
		}
