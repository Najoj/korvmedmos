/*
 * back_heuristics.hpp
 *
 *  Created on: 15 okt 2010
 *      Author: jacob
 */

#ifndef BACK_HEURISTICS_HPP_
#define BACK_HEURISTICS_HPP_


#include <cmath>
#include <string>
#include "../common.hpp"
#include "back_rules.hpp"
#include "../Board.hpp"
class BackHeuristics : public BackRules
{
	private:

	public:
	//See rules constructor for more intreseting stuff
	BackHeuristics(string b) : BackRules (b){
		//Improve the board, yay
		improve_board(this->board);
	}
	/**
	 * Used for local heuristics
	 * returns a cost for this direction
	 */
	int heuristics(int dir){

		int cost = 0;
	//	cost += jens_box_goal_distance(dir);
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





};
#endif /* BACK_HEURISTICS_HPP_ */
