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
		
		void improve_board(Board * board)
		{
			// hitta hörn
			for (int i = 0; i < board->width; i++)
			{
				for (int j = 0; j < board->height; j++)
				{
					if (board->get(i, j) == FLOOR) {
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
