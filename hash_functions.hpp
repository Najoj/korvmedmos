/*
 * hash_functions.hpp
 *
 *  Created on: 24 sep 2010
 *      Author: jacob
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
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 2617;
        return ((seed << 7) | (seed >> 7)) % FILTER_SIZE;
    }
};

struct hash3 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 1709;
        return ((seed << 23) | (seed >> 23)) % FILTER_SIZE;
    }
};

struct hash4 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 2243;
        return ((seed << 11) | (seed >> 11)) % FILTER_SIZE;
    }
};
struct hash5 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 809;
        return ((seed << 15) | (seed >> 15)) % FILTER_SIZE;
    }
};
struct hash6 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 1609;
        return ((seed << 31) | (seed >> 31)) % FILTER_SIZE;
    }
};
struct hash7 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 659;
        return ((seed << 21) | (seed >> 27)) % FILTER_SIZE;
    }
};
struct hash8 {
    size_t operator()(Node n) const{
        std::size_t seed = 0;
        boost::hash_combine(seed, n.getCurrent_position().x);
        boost::hash_combine(seed, n.getCurrent_position().y);
        for(int i=0;i<n.getLen();i++){
        boost::hash_combine(seed, n.boxes_positions[i].x);
        boost::hash_combine(seed, n.boxes_positions[i].y);

        }
        //Improve hash by primen number?
        seed = seed * 173;
        return ((seed << 30) | (seed >> 16)) % FILTER_SIZE;
    }
};

#endif /* HASH_FUNCTIONS_HPP_ */
