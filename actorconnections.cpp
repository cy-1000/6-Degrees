/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: A program that can tell, when given two actors, when the two actors became connected by any path.
 */
#include "ActorGraph.h"
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <istream>
#include <ostream> 
#include <fstream>
#include <sstream>


using namespace std;


#define NUM_ARGS 5

int main (int argc, char** argv){

	//if less than specified arguments return error code
	if (argc < NUM_ARGS || argc > NUM_ARGS){
		cout << "Invalid number of arguments" << endl;
		return -1;
	}


	//instantiate the variables
	std::string infile;
	std::string ufind;
	std::string pairs;
	std::string output;
	bool unionfind;


	std::vector<std::pair<std::string, std::string>> vecpairs;

	//init the variables
	infile = argv[1];
	ufind = argv[4];
	pairs = argv[2];
	output = argv[3];

	//if the flag passed in is ufind then set the flag to true
	if (ufind == "ufind"){
		unionfind = true;
	}
	//else we are using bfs to do actor connections
	else if (ufind == "bfs"){
		unionfind = false;
	}
	else{
		cout << "invalid input for kind of find to use" << endl;
		return -1;
	}

	ActorGraph graph;
	graph.loadFromFile(infile, false, true);


	// Initialize the file stream
	ifstream in(pairs);
	ofstream out(output);

	bool have_header = false;
	bool BFScalled = false;

    // keep reading lines until the end of file is reached
	while (in) {
		string s;

		if (in.eof()) {
			break;
		}

        // get the next line
		if (!getline( in, s )) break;

		if (!have_header) {
            // skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> pair;

		while (ss) {
			string next;

            // get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			pair.push_back(next);
		}

		if (pair.size() != 2) {
            // we should have exactly 2 columns
			continue;
		}

		vecpairs.push_back(std::make_pair(pair[0],pair[1]));


	}
	//if unionfind is specified then run the disjoint set connections
	if(unionfind){

		graph.actorConnectionsDJ(vecpairs, out);
	}
	//else run the BFS actorConnections
	else{
		graph.actorConnections(vecpairs, out);
	}

}
