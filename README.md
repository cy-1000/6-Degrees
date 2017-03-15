# 6-Degrees
6 Degrees of Kevin Bacon game 


Finds a path from one actor to another actor, connected by movies. Uses a database from IMDB dating up to movies released in 2015.

Has functionality to find the shortest path in an unweighted graph, a weighted graph, finding the path of movies that connect two actors. This is implemented in the pathfinder program.

Usage is as follows:
./pathfinder (moviedatabase) (u or w) (pairs file) (output file)

where moviedatabase is the movie_casts.tsv file, u or w specifes weighted or unweighted graph, pairs file is a file of tab seperated pairs of actors the program needs to find, and the output file is where it will write the paths. 

Also has the functionality of telling the year when 2 actors became connected...
usage is as follows

./actorconnections (moviedatabase) (pairs file) (out put file) ufind

where moviedatabase is the movie_casts.tsv file, the pairs file is the list of tab seperated pairs of actors you want to find out the year they were conencted , the output file is the file that you want to write the solutions to, and ufind is fixed, this tells the program to use the Disjoint Set data structure to find out whether two actors are connected. 
