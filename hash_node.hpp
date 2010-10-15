#ifndef HASH_NODE_HPP
#define HASH_NODE_HPP

#include "common.hpp"
#include "small_position.hpp"
#include "node.hpp"

class HashNode{
	SmallPosition * boxes_positions;
	SmallPosition jens;
	char len;

public:

	HashNode() {};

	/*
	Hashnode is made purely to be hashed by the hash-map. 
	It only saves the values that are supposed to be hashed.

	Can take values as Positions, they will be converted to SmallPositions
	to save space. 
	*/
	HashNode(Position jens, Position *boxes, char len){
		this->len = len;
		// Convert to smallposition. 
		this->jens = SmallPosition(jens);
		boxes_positions = new SmallPosition[len];
		for(int i = 0; i < len; i++){
			// Convert boxes to SmallPosition
			this->boxes_positions[i] = boxes[i];
		}
	}

	/*
	Copy constructor that takes a Node reference. This is for convenience
	to be able to copy a Node into a HashNode in this way:
	Node * n = new Node();
	HashNode * hn = new HashNode(*n);

	Or using references instead of pointers of course. 
	*/
	HashNode(Node & node){
		this->len = (char) node.getLen();	// node.len is private. Using getLen() instead.
		this->jens = node.getCurrent_position(); // node.jens is private, using getCurrent_position() instead.
		boxes_positions = new SmallPosition[len]; 
		Position * p = node.getBoxes();
		for(int i = 0; i < len; i++){
			this->boxes_positions[i] = p[i];	// Copy boxes. 
		}
	}

	/* 
	== Operator, to be used with the hash_table and the hash_function. 
	*/
	bool operator==(const HashNode & other) const
    {
            if (this->jens != other.jens)
                    return false;
            for (int i = 0; i < len; i++)
            {
                    if (this->boxes_positions[i] != other.boxes_positions[i])
                    return false;
            }
            return true;
    }

		/* 
	== Operator, to be used with the hash_table and the hash_function. This one takes a 
	Node parameter instead of a HashNode. Eases checking between Nodes and HashNodes. 
	*/
	bool operator==(Node & other) const
    {
		if (this->jens != other.getCurrent_position())	// other.jens is private.
                    return false;
            for (int i = 0; i < len; i++)
            {
                    if (this->boxes_positions[i] != other.getBoxes()[i]) // other.boxes_positions is private
                    return false;
            }
            return true;
    }
    

	/*
	Hash function, same as Node one, only changed to work with HashNode by using SmallPosition instead. 
	*/
    friend std::size_t hash_value(HashNode const& p)
    {
            std::size_t hash = 0;
            hash += 499973*p.jens.x() + 849731*p.jens.y();
            for(int i = 0; i < p.len; i++)
            {
                    hash += (612301*(p.boxes_positions[i].x()<<i)) ^ (1182463*p.boxes_positions[i].y());
            }
            return hash;
    }


};


#endif