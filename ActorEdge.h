/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: Header file for the ActorEdge class holding info containing the movies that an
 * ActorNode shares with another ActorNode
 */


#include <string>
#include <sstream>
#include <vector>

class ActorEdge{
protected:

	//Holds the movie information concatenated with the year
	std::string info;

	//the year of the movie
	int year;

	//weight of the edge itself
	int weight;




public:

	//constructor to make a new ActorEdge, making a pair of the from and to, and storing the movie information. 
	ActorEdge(std::string from, std::string to, std::string info);

	//Destructor for the ActorEdge
	~ActorEdge();

	//returns a string that is of the format [movie#@year] for the formatted output when writing paths
    std::string getFormatted();
    
    //Holds the information of both of the actors connected by this ActorEdge object
    std::pair<std::string, std::string> fromto;

    //Returns the weight of the given edge.
    int getWeight();

    //returns the Movie info related to this path. 
    std::string getInfo();
};
