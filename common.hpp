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
