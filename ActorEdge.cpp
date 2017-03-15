/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: .cpp file for the ActorEdge class and its methods
 */

#include "ActorEdge.h"

ActorEdge::ActorEdge(std::string from, std::string to, std::string info){
    this->fromto = std::make_pair(from , to);
    this->info = info;
}

ActorEdge::~ActorEdge(){
	this->fromto = std::make_pair("" , "");
	this->info = "";
}

std::string ActorEdge::getFormatted(){
	std::string formatted = this->info;

	std::istringstream ss( formatted );

	std::vector <std::string> pair;

	while (ss) {
		std::string next;

		if (!getline( ss, next, '\t' )) break;

		pair.push_back(next);
	}

	formatted = "[" + pair[0] +"#@"+ pair[1] + "]";

	return formatted;
}

int ActorEdge::getWeight(){

	std::string weight = this->info;

	std::istringstream ss( weight );

	std::vector <std::string> pair;

	while (ss) {
		std::string next;

		if (!getline( ss, next, '\t' )) break;

		pair.push_back(next);
	}

	weight = pair[1];

	return 1 + (2015 - (stoi(weight)));
}

std::string ActorEdge::getInfo(){
	return info;
}
