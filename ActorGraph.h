/* Author: Cy Hynes
 * Date:   2-27-17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "ActorEdge.h"
#include "Movie.h"
#include "UnionFind.h"




using namespace std;

//When passed in two ActorNode pointers ,dereference and then use compare 
class ActorNodeComp {
public:
    bool operator()(ActorNode* lhs, ActorNode* rhs) const {
        
        return *lhs < *rhs;

    }
};
//When passed in two Movie pointers ,dereference and then use compare 
class MovieNodeComp {
public:
    bool operator()(Movie* lhs, Movie* rhs) const {
        
        return *lhs < *rhs;

    }
};


class ActorGraph {
protected:

    //Holds all the ActorNode* for the graph
    std::unordered_map<std::string, ActorNode*> actorset;

    //vector of all actors to iterate over when needed
    std::vector<ActorNode*> actorvector;

    std::vector<ActorEdge*> edgevector;

    //Holds all the Movie* for the graph
    std::unordered_map<std::string, Movie*> movieset;

    //tracker for how many nodes are created
    int nodeCount;

    //tracker for how many edges are created
    int edgeCount;

    //tracker for how many movies are created
    int movieCount;

    //bool to see if weighted edges are needed
    bool useWeightedEdges; 

    //bool to see if the header in the input has already been processed
    bool headerwrite; 



public:

    //Consructor for the ActorGraph
    ActorGraph(void);

    //destructor
    ~ActorGraph();
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(std::string in_filename, bool use_weighted_edges, bool actorconnect);


    //Takes in actor name, movie title, movieyear and places them into graph data structures. Uses different methods on whether
    //it is a pathifnder program calling it or if it is a actorconnections program
    void placeInGraph(std::string & actor_name, std::string & movie_title, std::string & movie_year, bool actorconnect);
    
    //Makes connections between ActorNodes in the pathfinder graph     
    void makeConnections();

    //Breadth-First Search given a from and a to and whether is is pathfinder or actorconnect calling this function
    //takes in a ofstream in order to pass it on to writePairs()
    bool BFS(std::string & from, std::string & to, ofstream& out, bool actorconnect);

    //method to write the pairs to the output using ofstream to write to a file. 
    void writePairs(std::string & actor1, std::string & actor2, ofstream& out);

    //Tells whether the graph need Dijkstra's algo
    bool isDij();

    //Dijkstra's algorithm for searching through the graph
    void Dij(std::string & from, std::string & to, ofstream & out );

    //actor connections search using BFS
    void actorConnections(std::vector<std::pair<std::string,std::string>>& pairs, ofstream& out );

    //actor connections search using Disjoint sets
    void actorConnectionsDJ(std::vector<std::pair<std::string,std::string>>& pairs, ofstream& out );

    //clear the current connections so that new connections can be made
    void clearConnections();

  
};


#endif // ACTORGRAPH_H
