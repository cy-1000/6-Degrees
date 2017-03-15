/* Author: Cy Hynes
 * Date:   2-27-17
 *
 * Overview: .cpp file for the ActorGraph class outlining all the methods needed for pathfinder and actorconnections
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include "ActorGraph.h"

#define INFINITY std::numeric_limits<int>::max();


using namespace std;

ActorGraph::ActorGraph(void) {
	nodeCount = 0;
	edgeCount = 0;
	movieCount = 0;
	headerwrite = false; 
	useWeightedEdges = false;
}

ActorGraph::~ActorGraph(){
	clearConnections();
}

bool ActorGraph::loadFromFile(const std::string in_filename, bool use_weighted_edges, bool actorconnect) {
    // Initialize the file stream
	ifstream infile(in_filename);

	useWeightedEdges = use_weighted_edges;

	bool have_header = false;

    // keep reading lines until the end of file is reached
	while (infile) {
		string s;

        // get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
            // skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

            // get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
            // we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		string movie_year = (record[2]);

		//Places the node of the actor in the graph and additional movie info and year into the 
		//data structures of ActorGraph.
		placeInGraph(actor_name, movie_title, movie_year, actorconnect);


	}
	if(!actorconnect){
		//if its not an actorconnection program calling this function then run regualr connections
		//actorconnections get called by the actorconnections.cpp program
		makeConnections();
	}

	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}



void ActorGraph::placeInGraph(std::string & actor_name, std::string  & movie_title, std::string & movie_year, bool actorconnect){
    //append movie year to the title to get distinct movies
	std::string moviefull = movie_title;
	moviefull.append('\t' + movie_year);

    //if movie is not found in movie set, create new Movie object
	Movie* currentMovie;

	if (movieset[moviefull] == nullptr){
		currentMovie = new Movie(movie_title, stoi(movie_year));
		movieCount++;
		movieset[moviefull] = currentMovie;

	}
	else{
        //currentMovie gets assigned to already existing movie
		currentMovie = movieset[moviefull];
	}

	ActorNode* currentActor;

    //if actor has not been put into the hash map then create new ActorNode
	if (actorset[actor_name] == nullptr){
		currentActor = new ActorNode(actor_name);
		nodeCount++;
		actorset[actor_name] = currentActor;
		actorvector.push_back(currentActor);
		currentMovie->addActor(currentActor->info);

	}
	//assign the currentActor pointer to an existing actor in actorset
	else{
		currentActor = actorset[actor_name];
		currentMovie->addActor(currentActor->info);

	}
	
}



void ActorGraph::makeConnections(){
    //iterators to access the movie map
	auto itMap = movieset.begin();
	auto endMap = movieset.end();

	ActorNode* first;
	ActorNode* second;
	std::string firstname;
	std::string secondname;
	std::string currentMovieName;

	Movie* currentMovie;

    //iterate through all movies
	for (; itMap != endMap; itMap++){
        //name of the movie
		currentMovie = movieset.find(itMap->second->getFullName())->second;
        //if the current movie has more than one actor in it
		int sizeofactors = currentMovie->actorSize();

		if (sizeofactors > 1){

            //for every actor in the current movie create a ActorEdge connection
			for (int i = 0; i < sizeofactors; i++){
				for (int j = 0; j < sizeofactors; j++){
					if (j == i ){
						continue;
					}

					//find each actor 
					first = actorset.find(itMap->second->actors[i])->second;
					second = actorset.find(itMap->second->actors[j])->second;


					if(first->connections[second->info][currentMovie->getFullName()] == nullptr){

						firstname = first->info;
						secondname = second->info;
						currentMovieName = currentMovie->getFullName();

						//Create an ActorEdge object between the two actors
						ActorEdge* connection = new ActorEdge(firstname, secondname, currentMovieName);
						ActorEdge* & ref = connection;
						edgeCount++;

						//put the edge in both ActorNode's connections map
						first->connections[secondname][currentMovieName] = ref;
						second->connections[firstname][currentMovieName] = ref;
					}
				}
			}
		}
	}


	/*cout << nodeCount << " Nodes were created" << endl;
	cout << edgeCount << " Edges were created" << endl;
	cout << movieCount << " Movies were created" << endl;*/
}

void ActorGraph::actorConnections(std::vector<std::pair<std::string,std::string>>& pairs, ofstream& out){
	std::priority_queue<Movie*, std::vector<Movie*>, MovieNodeComp> orderedmovies;

	auto itMap = movieset.begin();
	auto endMap = movieset.end();

	for (; itMap != endMap; itMap++){
		orderedmovies.push(itMap->second);
	}

	ActorNode* first;
	ActorNode* second;
	std::string firstname;
	std::string secondname;
	std::string currentMovieName;
	bool connected;
	Movie* currentMovie;

	//mapped vectors to the pairs vector in order to keep track if it has 
	//been found and what year the pair became connected for printing
	std::vector<int> found(pairs.size(),0);
	std::vector<int> yearfound(pairs.size(), 0);

	int sizeofpairs = pairs.size();
	int numfound; 

	numfound = 0;

	while (!connected){

		int currentyear = orderedmovies.top()->year;

		while (currentyear == orderedmovies.top()->year) {

			if (orderedmovies.empty() || numfound == sizeofpairs){
				connected = true;
				break;
			}
       		//name of the movie		
			currentMovie = orderedmovies.top();
			orderedmovies.pop();

        	//if the current movie has more than one actor in it
			int sizeofactors = currentMovie->actorSize();

			if (sizeofactors > 1){

            	//for every actor in the current movie create a ActorEdge connection
				for (int i = 0; i < 1; i++){
					for (int j = 0; j < sizeofactors; j++){
						if (j == i ){
							continue;
						}

						first = actorset[currentMovie->actors[i]];
						second = actorset[currentMovie->actors[j]];

						//if the actor doesn't have an edge at the index of the second actor and 
						// the same for the reverse then create a new edge to connect these 
						//two actors 
						if(first->connections[second->info][currentMovie->getFullName()] == nullptr &&
							second->connections[first->info][currentMovie->getFullName()] == nullptr){

							firstname = first->info;
						secondname = second->info;
						currentMovieName = currentMovie->getFullName();


						ActorEdge* connection = new ActorEdge(firstname, secondname, currentMovieName);
						ActorEdge* & ref = connection;
						edgeCount++;

						//put the edge in both ActorNode's connections map
						first->connections[secondname][currentMovieName] = ref;
						second->connections[firstname][currentMovieName] = ref;


					}
				}
			}
		}
	}


	for (int i = 0; i < sizeofpairs; i++){
		if (found[i] == 1){
			//if they have already been found then continue.
			continue;
		}

		if(BFS(pairs[i].first, pairs[i].second, out, true)){
			//mark that pair is found
			found[i] = 1;
			//add the year it was found to yearfound vector
			yearfound[i] = currentMovie->year;	
			//increment the number of pair found
			numfound++;		
		}
		else{
			yearfound[i] == 9999;
		}
	}

}

	for (int j = 0; j < sizeofpairs; j++){
		if(j == 0){
		out << "Actor1" << '\t' << "Actor2" << '\t' << "Year" << endl;
	}
	out << pairs[j].first << '\t' << pairs[j].second << '\t' << yearfound[j] << endl; 
	}

	cout << nodeCount << " Nodes were created" << endl;
	cout << edgeCount << " Edges were created" << endl;
	cout << movieCount << " Movies were created" << endl;

}

void ActorGraph::actorConnectionsDJ(std::vector<std::pair<std::string,std::string>>& pairs, ofstream& out){
	//use a priority queue to sort by the year of each movie
	std::priority_queue<Movie*, std::vector<Movie*>, MovieNodeComp> orderedmovies;

	//create a unionFind data structure to see if the actors are connected
	UnionFind* uf = new UnionFind();

	auto itAct = actorset.begin();
	auto endAct = actorset.end();

	for (; itAct != endAct; itAct++){
		uf->addActor(itAct->second->info);
	}

	auto itMap = movieset.begin();
	auto endMap = movieset.end();

	for (; itMap != endMap; itMap++){
		orderedmovies.push(itMap->second);
	}

	ActorNode* first;
	ActorNode* second;
	std::string firstname;
	std::string secondname;
	std::string currentMovieName;
	bool connected;
	Movie* currentMovie;

	//mapped vectors to the pairs vector in order to keep track if it has 
	//been found and what year the pair became connected for printing
	std::vector<int> found(pairs.size(),0);
	std::vector<int> yearfound(pairs.size(), 0);

	int sizeofpairs = pairs.size();
	int numfound; 

	numfound = 0;

	while (!connected){

		int currentyear = orderedmovies.top()->year;

		while (currentyear == orderedmovies.top()->year ){

			
			if (orderedmovies.empty() || numfound == sizeofpairs){
				connected = true;
				break;
			}
       		 //name of the movie		
			currentMovie = orderedmovies.top();
			orderedmovies.pop();

        		//if the current movie has more than one actor in it
			int sizeofactors = currentMovie->actorSize();

			if (sizeofactors > 1){

            		//for every actor in the current movie create a ActorEdge connection
				for (int i = 0; i < sizeofactors; i++){
					for (int j = 0; j < sizeofactors; j++){
						if (j == i ){
							continue;
						}

						firstname = actorset[currentMovie->actors[i]]->info;
						secondname = actorset[currentMovie->actors[j]]->info;

						uf->unionsets(firstname,secondname);
					}
				}
			}
		}


		for (int i = 0; i < sizeofpairs; i++){
			if (found[i] == 1){
				continue;
			}
			if(uf->sameSet(pairs[i].first, pairs[i].second)){
				//mark that pair is found
				found[i] = 1;
				//add the year it was found to yearfound vector
				yearfound[i] = currentMovie->year;	
				//increment the number of pair found
				numfound++;


			}
		}

	}
	//output to the file
	for (int j = 0; j < sizeofpairs; j++){

		if(j == 0){
			out << "Actor1" << '\t' << "Actor2" << '\t' << "Year" << endl;
		}
		out << pairs[j].first << '\t' << pairs[j].second << '\t' << yearfound[j] << endl; 

	}

	delete uf;


	cout << nodeCount << " Nodes were created" << endl;
	cout << edgeCount << " Edges were created" << endl;
	cout << movieCount << " Movies were created" << endl;
	
}



bool ActorGraph::BFS(std::string & from, std::string & to, ofstream& out, bool actorconnect){

	auto itr = actorvector.begin();
	auto end = actorvector.end();

    //set all distances to infinity and other variables for a 
    //fresh BFS
	for (; itr != end; itr++){
		(*itr)->dist = INFINITY;
		(*itr)->edgeTaken = nullptr;
		(*itr)->prev = nullptr;
		(*itr)->done = false;
	}

	std::queue<ActorNode*> queue;
	ActorNode* start = actorset[from];
	ActorNode* target = actorset[to];
	start->dist = 0;
	start->prev = 0;
	queue.push(start);
    //cout << "pushed " << start->info << " into queue " << endl;

	bool found = false; 
	while ( !queue.empty() ){

		ActorNode* next = queue.front();
		queue.pop();

		std::string currentName = next->info;
		next->done = true;
        //cout << currentName << endl;


		auto itr = next->connections.begin();
		auto end = next->connections.end();

		for (; itr != end; ++itr){

			auto itr1 = itr->second.begin();
			auto end1 = itr->second.end();

			for(; itr1 != end1; itr1++){

				std::string nextActorName = itr1->second->fromto.first;

				if(currentName == nextActorName){
					nextActorName = itr1->second->fromto.second;
				}

				ActorNode* neighbor = actorset[nextActorName];

				//if the neighbor is the target
				//then mark fields then break
				if (neighbor == target){
					neighbor->dist = next->dist + 1;
					neighbor->prev = next;
					neighbor->edgeTaken = itr1->second;
					if(!actorconnect){
						writePairs(from, to, out);
					}
					return true; 
				}
				//if the neighbors distance is greater than 1 + current distance 
				//and is not done then update fields and push to queue for 
				//future exploration.
				else if (next->dist+1 < neighbor->dist && !neighbor->done){
					neighbor->dist = next->dist + 1;
					neighbor->prev = next;
					neighbor->edgeTaken = itr1->second;
					queue.push(neighbor);
				}
			}
		}

	}
	return false;

}


void ActorGraph::Dij(std::string & from, std::string & to, ofstream& out){

	auto itr = actorset.begin();
	auto end = actorset.end();

    //set all distances to infinity and other fields to the start values.
	for (; itr != end; itr++){
		itr->second->dist = INFINITY;
		itr->second->edgeTaken = nullptr;
		itr->second->prev = nullptr;
		itr->second->done = false;
	}

	std::priority_queue<ActorNode*, std::vector<ActorNode*>, ActorNodeComp> pqueue;
	//intial weight for the guess
	//this will circumvent the case where we push a node in,
	//the target node, and is stuck behind equal distance nodes 
	//this allows us to skip trivial pops of the queue when 
	//we have already found the shortest path to a certain 
	//node. 
	int equalweight = 9999;

	ActorNode* start = actorset.find(from)->second;
	ActorNode* target = actorset.find(to)->second;
	start->dist = 0;
	pqueue.push(start);

	bool found = false; 
	while ( !pqueue.empty() ){


		ActorNode* next = pqueue.top();
		pqueue.pop();
		//if the next distance is the equalweight or if the target is marked done writePairs
		if(target->done || next->dist == equalweight ){
			writePairs(from, to, out);
			break;
		}

		if(!next->done){

			next->done = true;

			std::string currentName = next->info;

			//iterate through all the connections of the current node.
			auto itr = next->connections.begin();
			auto end = next->connections.end();


			for (; itr != end; ++itr){

				auto itr1 = itr->second.begin();
				auto end1 = itr->second.end();

				for(; itr1 != end1; itr1++){

					//grab the actor that the edge goes to, check to see if 
					//it is the same name as the current actor
					std::string nextActorName = itr1->second->fromto.first;

					if(currentName == nextActorName){
						nextActorName = itr1->second->fromto.second;

					}

					ActorNode* neighbor = actorset.find(nextActorName)->second;
					
					//if taking this edge is less than the neighbors current distance 
					//then update fields of neighbor and push it into the priority_queue.
					if ((next->dist + itr1->second->getWeight()) < neighbor->dist){
						neighbor->dist = next->dist + itr1->second->getWeight();
						neighbor->prev = next;
						neighbor->edgeTaken = itr1->second;
						if (neighbor->info == to){
							if (neighbor->dist < equalweight){
								equalweight = neighbor->dist;
							}
						}
						pqueue.push(neighbor);
					}
					
				}
			}
		}
	}




}


void ActorGraph::writePairs(std::string & from, std::string & to, ofstream& out){
    //all nodes now have their distance from the start and the prev pointer chain to find the path

	ActorNode* curr = actorset[to];
	ActorNode* start = actorset[from];

	std::vector<std::string> path;


    //(actor)--[movie#@year]-->(actor)--...
	if (curr->dist == 0){
		return;
	}

	while (curr != start){
		std::string currName = curr->info;
		std::string prevName = curr->prev->info;
		std::string edgeTakenMovieName = curr->edgeTaken->getInfo();

		if (prevName == currName){
			break;
		}
		else{
            path.push_back(curr->info); //actor info
            path.push_back(curr->connections[prevName][edgeTakenMovieName]->getFormatted()); //movie title formatted
            curr = curr->prev;
        }
    }
    path.push_back(start->info);

    //path now holds the path in from the target node to the start node
    int pathsize = path.size();

    auto itr = path.begin();
    auto end = path.end();

    

    bool actor = true;
    //iterate in reverse to get the path from the start node to the target node
    for (int i = pathsize -1 ; i >= 0; i--){
    	if (headerwrite == false){
    		out << "(actor)--[movie#@year]-->(actor)--..." << endl;
    		headerwrite = true; 
    	}
    	if (actor){
    		if (i == 0){
    			out << "(" + path[i] + ")" << endl;
    			actor = !actor;
    		} 
    		else{
    			out << "(" + path[i] + ")" + "--";
    			actor = !actor;
    		}
    	}

    	else{

    		out << path[i] << "-->";
    		actor = !actor;
    	}

    }
}

bool ActorGraph::isDij(){
	return useWeightedEdges;
}

void ActorGraph::clearConnections(){

	//delete all actornodes
	auto itr = actorvector.begin();
	auto end = actorvector.end();

	for (; itr != end; itr++){
		(*itr)->clearConnections();
		delete *itr;
	}
	//delete all movies
	auto itr1 = movieset.begin();
	auto end1 = movieset.end();

	for (; itr1 != end1; itr1++){
		delete itr1->second;
	}

	actorset.clear();
	movieset.clear();

}






