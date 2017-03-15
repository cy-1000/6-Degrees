/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: Program that can find the shortest weighted or unweighted path in a given graph of movies and actors
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

	if (argc < NUM_ARGS || argc > NUM_ARGS){
		cout << "Invalid number of arguments" << endl;
		return -1;
	}

	std::string infile;
	std::string weighted;
	bool weight;
	std::string pairs;
	std::string output;
    bool dijcalled = false; 

	std::string pair0;
	std::string pair1;

	infile = argv[1];
	weighted = argv[2];
	pairs = argv[3];
	output = argv[4];

	if (weighted == "u"){
		weight = false;
	}
	else if (weighted == "w"){
		weight = true;
	}
	else{
		cout << "invalid input for weighted or unweighted" << endl;
		return -1;
	}

	ActorGraph graph;
	graph.loadFromFile(infile, weight, false);


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


        pair0 = pair[0];
        pair1 = pair[1];

        //if the graph is weighted call Dijkstra's method
        if(graph.isDij()){
        	cout << "Pair 0 and Pair 1 are " + pair0 + " // " + pair1 << endl;
            cout << "Calling to Dij()" << endl;
            graph.Dij(pair0, pair1, out);        	
        }
        //else the graph is unweighted
        else{
        	cout << "Calling to BFS() " << endl;
        	graph.BFS(pair0, pair1, out, false);
    	}

       
}
    in.close();
    out.close();

    return 0;
}