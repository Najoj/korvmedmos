/**
 * Stores all kinds of common and utility functions and structures.
 *
 */
#ifndef COMMON_HPP
#define COMMON_HPP
// Directions

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define USED  1337
// Board chars.
#define WALL '#'
#define BOX '$'
#define BOX_ONGOAL '*'
#define GOAL '.'
#define FLOOR ' '
// Him name is Jens
#define JENS '@'
#define JENS_ONGOAL '+'

// Chars on the board

/**
 * Common definitions
 */
#define FILTER_SIZE 1000000
//Defines board elements, see, http://www.sokobano.de/wiki/index.php?title=Level_format
/*
#define B_ELEM_WALL 35              // #     0x23
#define B_ELEM_PLAYER 64            // @     0x40
#define B_ELEM_PLAYER_GSQUARE 43    // +     0x2b
#define B_ELEM_BOX 36               // $     0x24
#define B_ELEM_BOX_GSQUARE 42       // *     0x2a
#define B_ELEM_GSQUARE 46           // .     0x2e
#define B_ELEM_FLOOR 32             // (Space)   0x20
*/
struct Position{
	int x;
	int y;
	Position(){}
	Position(int x, int y)
	{
		set(x,y);
	}
	void set(int x, int y)
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
};

const std::string moves_real[4] = {"U","R","D","L"};
#endif
