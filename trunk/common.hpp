/**
 * common.hpp
 *
 * Stores all kinds of common and utility functions and structures.
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <string>

// Directions
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NO_DIR 5

// Used for used node.
#define USED  1337

/* I do not think this is used

#ifdef DEBUG
	#define debug_print(text) cout<<text<<endl;
#endif

#define DEBUG 0
*/

/**
 * Defines board elements, see link:
 *   http://www.sokobano.de/wiki/index.php?title=Level_format
 */
// Board chars.
#define WALL '#'
#define BOX '$'
#define BOX_ONGOAL '*'
#define GOAL '.'
#define FLOOR ' '
// Him name is Jens
#define JENS '@'
#define JENS_ONGOAL '+'
#define BAD_POS 'x'

// Some numbers we use here and there.
#define FAIL -1
#define OK 1
#define LIMIT_EXCEEDED 2
#define JENS_IS_PUSHING_BOX_OK 4711
#define BIG_VALUE 2147483647
#define COST_TO_MOVE_BOX_ON_GOAL 15

/**
* Common definitions
*/
int revereseDir(int push_box_dir);
struct Position
{
	unsigned char x;
	unsigned char y;
	
	Position()
	{
		x=0;
		y=0;
	}
	Position(char x, char y)
	{
		set(x,y);
	}
	
	// Various setters and getters
	void set(char x, char y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Position & other) const
	{
		return (this->x == other.x) && (this->y == other.y);
	}
	bool operator!=(const Position & other) const
	{
		return !(*this == other);
	}
	Position operator+(const Position & other) const
	{
		return Position(other.x+this->x, other.y+this->y);
	}
	Position up()
	{
		return Position(x, y-1);
	}
	Position right()
	{
		return Position(x+1, y);
	}
	Position down()
	{
		return Position(x, y+1);
	}
	Position left()
	{
		return Position(x-1, y);
	}
	
	void addPosition(Position pos)
	{
		x += pos.x;
		y += pos.y;
	}
	
	// Get a direction
	Position getDirection(int dir)
	{
		switch(dir)
		{
		case LEFT:
			return left();
			break;
		case RIGHT:
			return right();
			break;
		case UP:
			return up();
			break;
		case DOWN:
			return down();
			break;
		default:
			return Position(0,0);
		}
	}
};

Position getXYDir(int, Position);

// Used to translate number 0-3 to a human readable direction.
const std::string moves_real[4] = {"U","R","D","L"};

#endif
