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

// Used for used node.
#define USED  1337

//#include <stdio.h>
#ifdef DEBUG
	#define debug_print(text) cout<<text<<endl;
#endif
// Rishie gillar  barn.

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
#define FAIL -1
#define JENS_IS_PUSHING_BOX_OK 4711
#define BIG_VALUE 2147483647

#define OK 1
#define DEBUG 0
// Chars on the board

/**
* Common definitions
*/

struct Position
{
	char x;
	char y;
	Position() {}
	
	Position(char x, char y)
	{
		set(x,y);
	}

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
	
	void addPosition(Position pos) {
		x += pos.x;
		y += pos.y;
	}

	Position getDirection(int dir){
		switch(dir){
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

		}
	}
};

const std::string moves_real[4] = {"U","R","D","L"};
#endif
