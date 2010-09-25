/*
 * hash_functions.hpp
 *
 *  Created on: 24 sep 2010
 *      Author: jacob
 *
 *
 *      It was a buffalo soldier in the heart of America,
	stolen from Africa, brought to America:

	Fighting on arrival,fighting for survival.
	I mean it, when I analyse the stench,
	to me it make a lot of sense.
	How did dreadlock rasta was buffalo soldier.

	And he was taken from Africa,
	brought to America.
	Fighting on arrival,fighting for survival.
	Say it was a buffalo soldier,dreadlock rasta.
	Buffalo soldier, in the heart of America.

	If you know your history,
	Then you would know where you coming from,
	Then you wouldnt have to ask me,
	Who the heck do you think I am.

	Im just a buffalo soldier in the heart of america,
	Stolen from africa, brought to america,
	Said he was fighting on arrival, fighting for survival;
	Said he was a buffalo soldier win the war for america.

	Dreadie, woy yoy yoy, woy yoy-yoy yoy,
	Woy yoy yoy yoy, yoy yoy-yoy yoy!
	Woy yoy yoy, woy yoy-yoy yoy,
	Woy yoy yoy yoy, yoy yoy-yoy yoy!
	Buffalo soldier troddin through the land, wo-ho-ooh!
	Said he wanna ran, then you wanna hand,
	Troddin through the land, yea-hea, yea-ea.

	Said he was a buffalo soldier win the war for america;
	Buffalo soldier, dreadlock rasta,
	Fighting on arrival, fighting for survival;
	Driven from the mainland to the heart of the caribbean.

	Singing, woy yoy yoy, woy yoy-yoy yoy,
	Woy yoy yoy yoy, yoy yoy-yoy yoy!
	Woy yoy yoy, woy yoy-yoy yoy,
	Woy yoy yoy yoy, yoy yoy-yoy yoy!

 */

#ifndef HASH_FUNCTIONS_HPP_
#define HASH_FUNCTIONS_HPP_

#include "common.hpp"

struct hash1 {
    size_t operator()(Node n) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 2129;
        return ((seed << 4) | (seed >> 4)) % FILTER_SIZE;
    }
};

struct hash2 {
    size_t operator()(Node n) const{
        std::size_t seed = 1567;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y*1337);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 2617;
        return ((seed << 7) | (seed >> 4)) % FILTER_SIZE;
    }
};

struct hash3 {
    size_t operator()(Node n) const{
        std::size_t seed =  4583;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        boost::hash_combine(seed, n.getCurrent_position().y);
        //Improve hash by primen number?
        seed = seed * 1709;
        return ((seed << 4) | (seed >> 6)) % FILTER_SIZE;
    }
};

struct hash4 {
    size_t operator()(Node n) const{
        std::size_t seed = 6607;
        boost::hash_combine(seed, n.getCurrent_position().y);
        boost::hash_combine(seed, n.getCurrent_position().x);

        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 2243;
        return ((seed << 3) | (seed >> 4)) % FILTER_SIZE;
    }
};
struct hash5 {
    size_t operator()(Node n) const{
        std::size_t seed =  3823;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);
        boost::hash_combine(seed, n.getCurrent_position().y);
        }
        //Improve hash by primen number?
        seed = seed * 809;
        return ((seed << 4) | (seed >> 4)) % FILTER_SIZE;
    }
};
struct hash6 {
    size_t operator()(Node n) const{
        std::size_t seed = 7307;

        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        //Improve hash by primen number?
        seed = seed * 1609;
        return ((seed << 16) | (seed >> 4)) % FILTER_SIZE;
    }
};
struct hash7 {
    size_t operator()(Node n) const{
        std::size_t seed = 5477;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 659;
        return ((seed << 2) | (seed >> 17)) % FILTER_SIZE;
    }
};
struct hash8 {
    size_t operator()(Node n) const{
        std::size_t seed = 7079;

        boost::hash_combine(seed, n.getCurrent_position().y);
        boost::hash_combine(seed, n.getCurrent_position().x);

        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }

        //Improve hash by primen number?
        seed = seed * 173;
        return ((seed << 13) | (seed >> 4)) % FILTER_SIZE;


    }
};

#endif /* HASH_FUNCTIONS_HPP_ */
