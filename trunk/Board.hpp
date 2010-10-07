/**
 * Board.hpp
 *
 * Representing the static parts of the Sokoban board. Which is the walls, the
 * floor and the goal positions.
 */

#ifndef BOARD_HPP
#define BOARD_HPP
#include "common.hpp"
#include <vector>
#include "node.hpp"
using namespace std;
struct Board
{
	protected:
		// This is the original position of Jens.
		Position jens;
		
	private:
		// Used for representing the entire board.
		int ** matrix;
		int ** cost_matrix;
		
	public:
		//TODO: Remove this variable.
		//This is the original position of the when the game starts
		vector<Position> goals;
		
		/**
		 * TODO: Does this need be public?
		 */
		// This is the original position of the boxes when the game starts
		vector<Position> boxes;
		
		// Width and height of the board.
		int width, height;
		
		Board() {}
		Board(int width, int height)
		{
			this->width = width;
			this->height = height;
			matrix = new int*[width];
		//	cost_matrix = new int*[width];
			for (int i = 0; i < width; i++)
				matrix[i] = new int[height];
		//		cost_matrix[i] = new int[height];
			//	cost_matrix[i] = 0;
		}
		bool xline_has_goal(int x)
		{
			for (int i = 0; i < height; i++)
			{
				if (get(x, i) == GOAL)
					return true;
			}
			return false;
		}
		bool yline_has_goal(int y)
		{
			for (int i = 0; i < width; i++)
			{
				if (get(i, y) == GOAL)
					return true;
			}
			return false;
		}
		void add_goal(Position p)
		{
			goals.push_back(p);
			matrix[p.x][p.y] = GOAL;
		}
		void set_floor(Position p)
		{
			matrix[p.x][p.y] = FLOOR;
		}
		int get(int x, int y)
		{
			// If we are outside to board.
			if(x < 0 || width <= x)
				return WALL;
			if(y < 0 || height <= y)
				return WALL;
			return matrix[x][y];
		}
		int get(Position p)
		{
			return get(p.x, p.y);
		}
		void set(int x, int y, int value)
		{
			matrix[x][y] = value;
		}
		void set(Position p, int value)
		{
			matrix[p.x][p.y] = value;
		}
		
		void insert_boxes(Position* boxes,int len)
		{
			for(int i = 0; i < len; i++)
			{
				if(matrix[boxes[i].x][boxes[i].y] == GOAL)
				{
					matrix[boxes[i].x][boxes[i].y] = BOX_ONGOAL;
				//	cout << "BOX_ONGOAL inserted (" << boxes[i].x << "," << boxes[i].y << endl;
				}
				else
				{
					matrix[boxes[i].x][boxes[i].y] = BOX;
				//	cout << "BOX inserted (" << boxes[i].x << "," << boxes[i].y << endl;
				}
			}
		}
		
		/**
		 * Denna gör en dum grejj med goals! Nån annan får fixa.
		 */
		void remove_boxes(Position* boxes,int len)
		{
			for(int i = 0; i < len; i++){
				if(matrix[boxes[i].x][boxes[i].y] == BOX_ONGOAL)
				{
					matrix[boxes[i].x][boxes[i].y] = GOAL;
				}
				else
				{
					matrix[boxes[i].x][boxes[i].y] = FLOOR;
				}
			}
		}
		
		Position * getJens()
		{
			return &jens;
		}
		
		void setJens(Position p)
		{
			jens = p;
		}
};
#endif
