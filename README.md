# Graph-isomorphism-algorithm
The input.txt contains the edges of the graph, which is used to create an adjacency matrix. Format of input file: first line 
contains the total number of vertices and the next eight line contains the vertices to which a particular vertiex is connected.
The first graph is the reference graph and all the other graphs (combinational graphs) are compared with the reference graph
for isomorphism.

The algorithm mimics 2-D combinational puzzle, where a puzzle is solved by achieving a particular combination starting from a 
random (scrambled) combination. The idea behind this algorithm follows the idea of achieving an adjacency matrix that matches
the adjacency matrix of reference graph. The algorithm achieves that by swapping rows and columns of the combinational graphs 
adjacency matrix. 


# Executing-samples
INPUT txt format:-
First line is number_of_vertices
and the next number_of_vertices lines is the connectivity for individual vertices

'input_file' variable is the name of the text file

To compile:-
 g++ -std=c++0x  -o isomorphism isomorphism.cpp

Provided a set of sample input text files. For each text file the first graph is reference matrix and the rest of the graphs are combinational matrices.
The output tells which graphs are isomorphic to the reference matrix and which are not.
Each graph has a distinct number which depends on the order/position of the graph in the text file.


# TODO
In this algorithm i tried to find a pattern between set of rotations which results in a configuration that was encountered before. A easier 
approach is to maintain a list of all the configuration that were encountered and match it with the current, but it is not an efficient solution.

# OUTPUT FORMAT
1. Reference Matrix which is compared with all the other Matrix.
2. Combinational Matrix which undergo rotation.
3. Result: IS OR NOT Isomorphic
4. Mapping of vertices of the two graphs/matrix.
5. Combinational Matrix after rotation and number of rotations were performed before getting to the result.

eg:

Reference matrix before Rotations/Swappings...

1 1 2 3 4 5 6 7 8 

1 0 1 0 0 1 0 0 1 

2 1 0 1 0 0 1 0 0 

3 0 1 0 1 0 0 1 0 

4 0 0 1 0 1 0 0 1 

5 1 0 0 1 0 1 0 0 

6 0 1 0 0 1 0 1 0 

7 0 0 1 0 0 1 0 1 

8 1 0 0 1 0 0 1 0 

Combinational matrix before Rotations/Swappings...

5 1 2 3 4 5 6 7 8 

1 0 0 0 1 0 0 1 1 

2 0 0 0 0 0 1 1 1 

3 0 0 0 0 1 1 1 0 

4 1 0 0 0 1 1 0 0 

5 0 0 1 1 0 0 0 1 

6 0 1 1 1 0 0 0 0 

7 1 1 1 0 0 0 0 0 

8 1 1 0 0 1 0 0 0 

Graph 1 & 5 are ISOMORPHIC

Mapping of the graphs

1	2	3	4	5	6	7	8	

8	2	6	4	1	7	3	5	


Combinational matrix after 7 Rotations/Swappings...

5 8 2 6 4 1 7 3 5 

8 0 1 0 0 1 0 0 1 

2 1 0 1 0 0 1 0 0 

6 0 1 0 1 0 0 1 0 

4 0 0 1 0 1 0 0 1 

1 1 0 0 1 0 1 0 0 

7 0 1 0 0 1 0 1 0 

3 0 0 1 0 0 1 0 1 

5 1 0 0 1 0 0 1 0 
##########################################################
##########################################################
