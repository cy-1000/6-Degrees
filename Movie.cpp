/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: .cpp file for the Movie class holding it's methods
 */


#include "Movie.h"
#include <string>

Movie::Movie(std::string movie_title, int year){
	this->movie_title = movie_title;
	this->year = year;
}

void Movie::addActor(std::string actor){
	this->actors.push_back(actor);
}

std::string Movie::getFullName(){
	//add a tab to keep format the same
	std::string fullName = movie_title;
	fullName.append('\t' + std::to_string(year));

	return fullName;
}


int Movie::actorSize(){
	return this->actors.size();
}

bool Movie::operator<(const Movie& other){
	//earlier year is a higher priority. 
    if(this->year != other.year){
        return this->year > other.year;
    }
    
    return this->movie_title < other.movie_title;
}
