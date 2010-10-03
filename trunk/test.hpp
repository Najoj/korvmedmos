/*
 * test.hpp
 *
 * 
 */

#ifndef TEST_HPP_
#define TEST_HPP_

#include <boost/bloom_filter.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/functional/hash.hpp>
#include <boost/fusion/tuple.hpp>



#include "node.hpp"
#include "common.hpp"

//en miljon
#define STORT_TAL 1000000
#define NUM_BOXES 8

#define X 11
#define Y 9


using namespace std;

using boost::function;
using boost::static_bloom_filter;
using boost::fusion::tuple;
using boost::fusion::make_tuple;

using boost::array;
using boost::function;
void test(){

    typedef static_bloom_filter<Node, FILTER_SIZE, tuple<hash1, hash2, hash3, hash4, hash5, hash6, hash7, hash8 > > filter_type;
    filter_type filter(make_tuple(hash1(), hash2(), hash3(), hash4(), hash5(), hash6(), hash7(), hash8()));

    Position boxes[NUM_BOXES];
	Position jens;
	jens.x = 0;
	jens.y = 0;

	int iterations = 0;
	int collisions = 0;
	for(unsigned int box = 0; box<NUM_BOXES; box++){
		for(unsigned int j = 0; j<X; j++){
			for(unsigned int k = 0; k<Y; k++){
				//Uppdatera boxens position.
				boxes[box].x = j;
				boxes[box].y = k;
				for(unsigned int jx = 0; jx < X ; jx++){
					for(unsigned int jy = 0; jy < Y ; jy++){
						jens.x = jx;
						jens.y = jy;
						Node n(jens,jens,boxes,NULL,NUM_BOXES);
						if(filter.contains(n)){
						//	cout << "\t COLLIDED: "<<endl;
							collisions++;
						}
					//	n.print();
						filter.insert(n);
						iterations++;
						}
					}
				}
			}
		}
	double d = ((double)collisions/(double)iterations)*100;
	cout.precision(15);
	cout <<"" << d << "%" << endl;
	cout << "Iterations " << iterations <<  "  Collisions " << collisions << endl;
	//  new Node()

}

#endif /* TEST_HPP_ */
