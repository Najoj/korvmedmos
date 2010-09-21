/**
 * Stores all kinds of common and utility functions and structures.
 *
 */

// Directions
#ifndef UP
#define UP 1
#endif
#ifndef RIGHT
#define RIGHT 2
#endif
// Down is negative UP, RIGHT is negative LEFT.
#ifndef DOWN
#define DOWN -1
#endif
#ifndef LEFT
#define LEFT -2
#endif

// Board chars.
#ifndef WALL
#define WALL '#'
#endif
#ifndef BOX
#define BOX '$'
#endif
#ifndef BOX_ONGOAL
#define BOX_ONGOAL '*'
#endif
#ifndef GOAL
#define GOAL '.'
#endif
#ifndef FLOOR
#define FLOOR ' '
#endif
// Him name is Jens
#ifndef JENS
#define JENS '@'
#endif
#ifndef JENS_ONGOAL
#define JENS_ONGOAL '+'
#endif

// Chars on the board


#ifndef COMMON_HPP
#define COMMON_HPP
/**
 * Common definitions
 */

//Defines board elements, see, http://www.sokobano.de/wiki/index.php?title=Level_format
/*
#define B_ELEM_WALL 35              //#     0x23
#define B_ELEM_PLAYER 64            //@     0x40
#define B_ELEM_PLAYER_GSQUARE 43    //+     0x2b
#define B_ELEM_BOX 36               //$     0x24
#define B_ELEM_BOX_GSQUARE 42       //*     0x2a
#define B_ELEM_GSQUARE 46           //.     0x2e
#define B_ELEM_FLOOR 32             //(Space)   0x20
*/
struct Position{
	int x;
	int y;
};
#endif
