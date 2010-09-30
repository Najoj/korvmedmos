/*
* hash_functions.hpp
*
*  Created on: 24 sep 2010
*      Author: jacob
*
*		[Repeat x2]
		My milkshake brings all the boys to the yard,
		And their like
		It's better than yours,
		Damn right it's better than yours,
		I can teach you,
		But I have to charge

		I know you want it,
		The thing that makes me,
		What the guys go crazy for.
		They lose their minds,
		The way I wind,
		I think its time

		[Chorus x2]
		La la-la la la,
		Warm it up.
		Lala-lalala,
		The boys are waiting

		My milkshake brings all the boys to the yard,
		And their like
		It's better than yours,
		Damn right it's better than yours,
		I can teach you,
		But I have to charge

		I can see youre on it,
		You want me to teach thee
		Techniques that freaks these boys,
		It can't be bought,
		Just know, thieves get caught,
		Watch if your smart,

		[Chorus x2]
		La la-la la la,
		Warm it up,
		La la-la la la,
		The boys are waiting,

		My milkshake brings all the boys to the yard,
		And their like
		It's better than yours,
		Damn right it's better than yours,
		I can teach you,
		But I have to charge

		Oh, once you get involved,
		Everyone will look this way-so,
		You must maintain your charm,
		Same time maintain your halo,
		Just get the perfect blend,
		Plus what you have within,
		Then next his eyes are squint,
		Then he's picked up your scent,

		[Chorus x2]
		Lala-lalala,
		Warm it up,
		Lala-lalala,
		The boys are waiting,

		My milkshake brings all the boys to the yard,
		And their like
		It's better than yours,
		Damn right it's better than yours,
		I can teach you,
		But I have to charge

*/

#ifndef HASH_FUNCTIONS_HPP_
#define HASH_FUNCTIONS_HPP_

#include "common.hpp"

struct hash1
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y);
		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		// Improve hash with a prime number
		seed = seed * 2129;
		return ((seed << 4) | (seed >> 4)) % FILTER_SIZE;
	}
};

struct hash2
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 1567;
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y*1337);
		for(int i=0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		// Improve hash with a prime number
		seed = seed * 2617;
		return ((seed << 7) | (seed >> 4)) % FILTER_SIZE;
	}
};

struct hash3
{
	size_t operator()(Node n) const
	{
		std::size_t seed =  4583;
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y);
		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		boost::hash_combine(seed, n.getCurrent_position().y);
		// Improve hash with a prime number
		seed = seed * 1709;
		return ((seed << 4) | (seed >> 6)) % FILTER_SIZE;
	}
};

struct hash4
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 6607;
		boost::hash_combine(seed, n.getCurrent_position().y);
		boost::hash_combine(seed, n.getCurrent_position().x);

		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		// Improve hash with a prime number
		seed = seed * 2243;
		return ((seed << 3) | (seed >> 4)) % FILTER_SIZE;
	}
};
struct hash5
{
	size_t operator()(Node n) const
	{
		std::size_t seed =  3823;
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y);
		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
			boost::hash_combine(seed, n.getCurrent_position().y);
		}
		// Improve hash with a prime number
		seed = seed * 809;
		return ((seed << 4) | (seed >> 4)) % FILTER_SIZE;
	}
};

struct hash6
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 7307;

		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y);
		// Improve hash with a prime number
		seed = seed * 1609;
		return ((seed << 16) | (seed >> 4)) % FILTER_SIZE;
	}
};

struct hash7
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 5477;
		boost::hash_combine(seed, n.getCurrent_position().x);
		boost::hash_combine(seed, n.getCurrent_position().y);
		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}
		// Improve hash with a prime number
		seed = seed * 659;
		return ((seed << 2) | (seed >> 17)) % FILTER_SIZE;
	}
};

struct hash8
{
	size_t operator()(Node n) const
	{
		std::size_t seed = 7079;

		boost::hash_combine(seed, n.getCurrent_position().y);
		boost::hash_combine(seed, n.getCurrent_position().x);

		for(int i = 0; i < n.getLen(); i++)
		{
			boost::hash_combine(seed, n.boxes_positions[i].x);
			boost::hash_combine(seed, n.boxes_positions[i].y);
		}

		// Improve hash with a prime number
		seed = seed * 173;
		return ((seed << 13) | (seed >> 4)) % FILTER_SIZE;

	}
};

#endif /* HASH_FUNCTIONS_HPP_ */
