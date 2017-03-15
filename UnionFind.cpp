/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: .cpp file for the Movie class holding it's methods
 */



#include "UnionFind.h"
#include <iostream>

using namespace std;

UnionFind::UnionFind(){
	size = 0;
}

void UnionFind::addActor(std::string& name){

	//np stands for no parent meaning it is a sentinel node
	sets.insert({name, "np"});
	size++;
}

std::string UnionFind::find(std::string& name){

	//find the value that is stored at the queried actor
	auto currentparent = sets.find(name);

	//if it is no parent then it is a sentinel node
	if(currentparent->second == "np"){
		return name;
	}
	//else keep iteratoring through until you find the sentinel node
	//uses path compression setting each node we look at to the eventual
	//sentinel node. 

	while(currentparent->second != "np"){
		currentparent->second = find(currentparent->second);
		currentparent = sets.find(currentparent->second);
	}

	//return the name of the sentienl node. 
	return currentparent->first;

}

bool UnionFind::sameSet(std::string& actor1, std::string& actor2){
	//if they are returning the same sentinel node 
	// then they are in the same set 
	if (find(actor1) == find(actor2)){
		return true;
	}
	//otherwise they are not in the same set 
	else{
		return false; 
	}
}

void UnionFind::unionsets(std::string& actor1, std::string& actor2){


	//if they are not in the same set
 	if (this->find(actor1) != this->find(actor2)){

 		auto itr = sets.find(find(actor2));
 		if (itr != sets.end()){

 			//set the value of the actor 2 to the sentinel of actor 1
 			itr->second = find(actor1);

 		}
	}
	
}

int UnionFind::getSize(){
	return size;
}
