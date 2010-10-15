#ifndef BOXLOCKS_HPP
#define BOXLOCKS_HPP

#include "common.hpp"

#define lock1 {\
	{0, 0, WALL},\
	{0, BOX, BOX},\
	{0, WALL, 0}}
#define lock2 {\
	{0, WALL, 0},\
	{BOX, BOX, 0},\
	{WALL, 0, 0}}
#define lock3 {\
	{0, WALL, 0},\
	{0, BOX, BOX},\
	{0, 0, WALL}}
#define lock4 {\
	{WALL, 0, 0},\
	{BOX, BOX, 0},\
	{0, WALL, 0}}
	
#define lock5 {\
	{0, 0, 0},\
	{0, BOX, WALL},\
	{WALL, BOX, 0}}
#define lock6 {\
	{0, BOX, WALL},\
	{WALL, BOX, 0},\
	{0, 0, 0}}
#define lock7 {\
	{0, 0, 0},\
	{WALL, BOX, 0},\
	{0, BOX, WALL}}
#define lock8 {\
	{WALL, BOX, 0},\
	{0, BOX, WALL},\
	{0, 0, 0}}
	
#define lock9 {\
	{0, WALL, WALL},\
	{0, BOX, BOX},\
	{0, 0, 0}}
#define lock10 {\
	{WALL, WALL, 0},\
	{BOX, BOX, 0},\
	{0, 0, 0}}
#define lock11 {\
	{0, 0, 0},\
	{0, BOX, BOX},\
	{0, WALL, WALL}}
#define lock12 {\
	{0, 0, 0},\
	{BOX, BOX, 0},\
	{WALL, WALL, 0}}
	
#define lock13 {\
	{0, 0, 0},\
	{0, BOX, WALL},\
	{0, BOX, WALL}}
#define lock14 {\
	{0, BOX, WALL},\
	{0, BOX, WALL},\
	{0, 0, 0}}
#define lock15 {\
	{0, 0, 0},\
	{WALL, BOX, 0},\
	{WALL, BOX, 0}}
#define lock16 {\
	{WALL, BOX, 0},\
	{WALL, BOX, 0},\
	{0, 0, 0}}

#define lock17 {\
	{0, 0, 0},\
	{0, BOX, BOX},\
	{0, BOX, BOX}}
#define lock18 {\
	{BOX, BOX, 0},\
	{BOX, BOX, 0},\
	{0, 0, 0}}
#define lock19 {\
	{0, BOX, BOX},\
	{0, BOX, BOX},\
	{0, 0, 0}}
#define lock20 {\
	{0, 0, 0},\
	{BOX, BOX, 0},\
	{BOX, BOX, 0}}

#define lock21 {\
	{WALL, BOX, 0},\
	{BOX, BOX, 0},\
	{0, 0, 0}}
#define lock22 {\
	{0, WALL, BOX},\
	{0, BOX, BOX},\
	{0, 0, 0}}
#define lock23 {\
	{0, 0, 0},\
	{WALL, BOX, 0},\
	{BOX, BOX, 0}}

#define lock24 {\
	{BOX, WALL, 0},\
	{BOX, BOX, 0},\
	{0, 0, 0}}
#define lock25 {\
	{0, BOX, WALL},\
	{0, BOX, BOX},\
	{0, 0, 0}}
#define lock26 {\
	{0, 0, 0},\
	{0, BOX, WALL},\
	{0, BOX, BOX}}

#define lock27 {\
	{BOX, BOX, 0},\
	{WALL, BOX, 0},\
	{0, 0, 0}}
#define lock28 {\
	{0, 0, 0},\
	{BOX, BOX, 0},\
	{WALL, BOX, 0}}
#define lock29 {\
	{0, 0, 0},\
	{0, BOX, BOX},\
	{0, WALL, BOX}}

#define lock30 {\
	{BOX, BOX, 0},\
	{BOX, WALL, 0},\
	{0, 0, 0}}
#define lock31 {\
	{0, 0, 0},\
	{BOX, BOX, 0},\
	{BOX, WALL, 0}}
#define lock32 {\
	{0, 0, 0},\
	{0, BOX, BOX},\
	{0, BOX, WALL}}

#define NUMBER_OF_LOCKS 32
int boxlocks[NUMBER_OF_LOCKS][3][3] = {lock1, lock2, lock3, lock4, lock5, lock6,
	lock7, lock8, lock9, lock10, lock11, lock12, lock13, lock14, lock15, lock16,
	lock17, lock18, lock19, lock20, lock21, lock22, lock23, lock24, lock25,
	lock26, lock27, lock28, lock29, lock30, lock31, lock32};

#endif
