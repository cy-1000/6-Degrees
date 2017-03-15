/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: Header file for the Movie class holding info on the movie and what actors acted in it
 */


#include <string>
#include <vector>


class Movie{


public:

	//Constructor creates a new Movie object
	Movie(std::string movie_title, int year);

	//adds a actorname to the actors vector
	void addActor(std::string actor);

	//get the name with the year concatenated
	std::string getFullName();

	//overloaded < operator to compare movie objects
	bool operator<(const Movie& other);

	//return the size of the actors vector	
	int actorSize();

	//vector of actors that have acted in this movie
	std::vector<std::string> actors;

	//name of the movie
	std::string movie_title;

	//year of the movie
	int year;

};
