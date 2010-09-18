#include "node.hpp"


Node::Node(){

}

Node::Node(int len){

	boxes_positions = new Position[len];
}

//Do cleanup.
Node::~Node(){

}

//Node Node::getChildren(){
//	return false;
//}

