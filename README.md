# Graph-isomorphism-algorithm
The input.txt contains the name of text file that is being read, those text files contains the graph connectivity information,
which is used to create an adjacency matrix. 
Format of input text files: first line contains the total number of vertices and the next eight line contains the vertices to which a particular vertiex is connected. The first graph is the reference graph and all the other graphs (combinational graphs) are compared with the reference graph
for isomorphism.

The algorithm mimics 2-D combinational puzzle, where a puzzle is solved by achieving a particular combination starting from a 
random (scrambled) combination. The idea behind this algorithm follows the idea of achieving an adjacency matrix that matches
the adjacency matrix of reference graph. The algorithm achieves that by swapping rows and columns of the combinational graphs 
adjacency matrix. 


# Executing-samples
INPUT txt format:-
First line is number_of_vertices
and the next number_of_vertices lines is the connectivity for individual vertices starting from 1 to number_of_vertices


To compile:-
 g++ -std=c++0x  -o isomorphism isomorphism.cpp

Provided a set of sample input text files. For each text file the first graph is reference matrix and the rest of the graphs are combinational matrices.
The output tells which graphs are isomorphic to the reference matrix and which are not.
Each graph has a distinct number which depends on the order/position of the graph in the text file.
