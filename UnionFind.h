/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: Header file for the Disjoint Set data structure.
 */

#include <unordered_map>
#include <string>
#include <iostream>
#include <cstring>


class UnionFind{  


	public:

		//constructor for the UnionFind data structure
		UnionFind();

		//combines the sets of actor1 and actor2 in the UnionFind data structure
		void unionsets(std::string& actor1, std::string& actor2);

		//adds an actor into the UnionFind data structure
		void addActor(std::string& name);

		//returns the # of actors in the UnionFind data structure 
		int getSize();

		//Finds the sentinel node of the given actor telling what set it belongs to
		std::string find(std::string& actor);

		//returns true or false on if the actors are in the same set
		bool sameSet(std::string& actor1, std::string& actor2);

		//the size of the actors in the UnionFind data structure. 
		int size;

		//keeps track of all the sets in the UnionFind data strucutre. 
		std::unordered_map<std::string, std::string> sets;


};
