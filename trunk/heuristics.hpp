/**
 * heuristics.hpp
 * 
 * Here is where we have our own search improvemnts.
 */
#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include <cmath>
#include "common.hpp"

class Heuristics
{
	private:
		
	public:
		int length_to_box(Position jens, Position box)
		{
			return sqrt((jens.x - box.x)*(jens.x - box.x) + (jens.y-box.y)*(jens.y-box.y));
		}
		
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
#endif
