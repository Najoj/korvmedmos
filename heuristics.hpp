/**
 * heuristics.hpp
 * 
 * Here is where we have our own search improvemnts.
 */
#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include <cmath>
#include <string>
#include "common.hpp"
#include "rules.hpp"
#include "Board.hpp"
class Heuristics : public Rules
{
	private:
		
	public:
	//See rules constructor for more intreseting stuff
	Heuristics(string b) : Rules (b){
		//Improve the board, yay
		improve_board(this->board);
	}
	/**
	 * Used for local heuristics
	 * returns a cost for this direction
	 */
	int heuristics(int dir){

		int cost = 0;
		cost += jens_box_goal_distance(dir);
		return cost;

	}
	/**
	 * Returns the lenght from jens to the closes box
	 */
	int length_from_jens_to_box(int dir, Node * parent)
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
				save = length_to_box(new_jens, parent->getBoxes()[i]);
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


	/**
	 * Removes deadlocks from the board
	 */
	void improve_board_wall_deadlocks_y(Board * board, int x, int y, int side){

			if(board->get(x,y-1) != WALL){
					return;	//Spårat
				}
			//check Y-dir left wall
		for(int k = y; k<board->height;k++){
			if(board->get(x,k) == GOAL || board->get(x+side,k) != WALL){
				break;
			}
			if(board->get(x,k) == WALL){
			//Mark all tested as X.
				int l = y;
				for(; l<k; l++){
					board->set(x,l, BAD_POS);

				}
				break;
			}

			}
		}
	/**
	 * Remove deadlocks from the board
	 */
		void improve_board_wall_deadlocks_x(Board * board, int x, int y, int side){
			if(board->get(x-1,y) != WALL){
			return;	//Spårat
			}
			//check x-dir left wall
		for(int k = x; k < board->width;k++){
			if(board->get(k,y) == GOAL || board->get(k,y+side) != WALL){
				break;
			}
			if(board->get(k,y) == WALL){
			//Mark all tested as X.
				for(int l = x; l<k; l++){
					board->set(l,y, BAD_POS);
				}
				break;
			}

			}
		}
		/**
		 * Removes corner dead locks
		 */
		void improve_board(Board * board)
		{
			// hitta hörn
			for (int i = 0; i < board->width; i++)
			{
				for (int j = 0; j < board->height; j++)
				{
					if (board->get(i, j) == FLOOR || board->get(i, j) == BAD_POS) {

						/**
						 * Avoids corners
						 */

						//Remove wall deadlocks
						improve_board_wall_deadlocks_y(board, i,j, 1);
						improve_board_wall_deadlocks_y(board,i,j, -1);

						improve_board_wall_deadlocks_x(board, i,j, 1);
						improve_board_wall_deadlocks_x(board, i,j, -1);

						// check up-right
						if (board->get(i, j-1) == WALL && board->get(i+1, j) == WALL)
						{
							board->set(i, j, BAD_POS);
							continue;
						}
						// check right-down
						if (board->get(i+1, j) == WALL && board->get(i, j+1) == WALL)
						{
							board->set(i, j, BAD_POS);
							continue;
						}
						// check down-left
						if (board->get(i, j+1) == WALL && board->get(i-1, j) == WALL)
						{
							board->set(i, j, BAD_POS);
							continue;
						}
						// check left-up
						if (board->get(i-1, j) == WALL && board->get(i, j-1) == WALL)
						{
							board->set(i, j, BAD_POS);
							continue;
						}
					}
					
				}	
			}
			// hitta kant utan mål
		}

/**
 * Calculates the distance from jens to the closest box + from that box to finish
 */
int jens_box_goal_distance(int dir)
	{
		//bool debug = false;
		//int debug_nr = 0;
		int min = BIG_VALUE, save, push_box_dir = NO_DIR;
		Position nearest_box, nearest_goal;
		Position temp;
		int jens_to_push_box_dir, box_to_goal_distance;
		int cost = 0;

	//	Position new_jens = getXYDir(dir, node_in_process->getCurrent_position());
		//Raden ovan funkar om den kompilerar, hoppas den undre gör de osså

		Position new_jens = node_in_process->getCurrent_position();
		new_jens.addPosition(getXYDir(dir));

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
	/**
	 * Return the cost to get the nearest box to goal
	 */
	int box_goal_distance(Node * parent, Position &jens){


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



			//cout << "DDD" << (int) nearest_box.x << " " << (int)nearest_box.y << endl;
			//cout << "DDD" << (int)nearest_goal.x << " " << (int)nearest_goal.y << endl;


			//Removes the boxes and goal positions
			board->set(nearest_box,WALL);
			board->set(nearest_goal, WALL);

			jens = nearest_goal;


			return cost;
	}
	/**
	* Tries to figure out the distance to the goal.
	*/
	int total_goal_distance(Node * parent){
	//bool debug = false;
	//int debug_nr = 0;
	int cost = 0;


	Position p = parent->getCurrent_position();
	//Must add boxes first

	for(short i = 0; i<parent->getLen(); i++){
			cost += box_goal_distance(parent,p);
			//cout << "COST" << cost << endl;
	}



	//cout << "TOTAL KOSTNAD: " << cost << endl;
	return 10*cost;

	}

	/**
	 * Checks if jens is adjacent to a goal position
	 */
	bool jens_next_to_goal(Node * n){
		//Check left
		if(board->get(n->getCurrent_position().left()) == GOAL){
			return true;
		}
		//Check right
		if(board->get(n->getCurrent_position().right()) == GOAL){
			return true;
		}
		//Check up
		if(board->get(n->getCurrent_position().up()) == GOAL){
			return true;
		}
		//Check down
		if(board->get(n->getCurrent_position().down()) == GOAL){
			return true;
		}
		return false;
	}
};
#endif
