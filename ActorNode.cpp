/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: .cpp file for the ActorNode class and its methods
 */


#include "ActorNode.h"
#include "ActorEdge.h"
#include <limits>
#include <iostream>

#define INFINITY std::numeric_limits<int>::max();


ActorNode::ActorNode(std::string actorName){
	//init all the nodes for a BFS to be performed correctly
	this->info = actorName;
	this->edgeTaken = nullptr;
	this->prev = nullptr;
	this->dist = INFINITY;
}

bool ActorNode::operator<(const ActorNode& other){
	//compare by distance, larger distances are of lower priority.
	if(this->dist != other.dist){
		return this->dist > other.dist;
	}

	return this->info > other.info;
}

void ActorNode::clearConnections(){
	//clear the connections map
	this->connections.clear();
	
}

