/* Author: Cy Hynes
 * Date: 2-27-17
 * Assignment: PA 4
 * Overview: Header file for the ActorNode class, containing information about the actor and the 
 * vector of ActorNodes it is connected to.
 */

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//forward actoredge to avoid circular dependencies. 
class ActorEdge;


class ActorNode{

public:

    //actor name
	std::string info;

    //constructor that creates a new ActorNode with passed in name
    ActorNode(std::string actorName);

    //Holds the connections of all the actors this ActorNode is connected to when loading the graph from file
    std::unordered_map<std::string, std::unordered_map<string, ActorEdge*> > connections;
    
    //distance from the start node in the various searches actorGraph can perform
    int dist;

    //the ActorEdge that was taken to get to the current ActorNode
    ActorEdge* edgeTaken;

    //the previous actor before reaching the current ActorNode
    ActorNode* prev;

    //boolean to see if the node has been visited
    bool done;

    //Overloaded < operator to compare ActorNode's by distance
    bool operator<(const ActorNode& other);

    //helper to clear the Connections for the destructor. 
    void clearConnections();

};
