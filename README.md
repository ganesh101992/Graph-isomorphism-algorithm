# Graph-isomorphism-algorithm

The input.txt contains the edges of the graph, which is used to create an adjacency matrix. Format of input file: first line 
contains the total number of vertices and the next eight line contains the vertices to which a particular vertiex is connected.
The first graph is the reference graph and all the other graphs (combinational graphs) are compared with the reference graph
for isomorphism.

The algorithm mimics 2-D combinational puzzle, where a puzzle is solved by achieving a particular combination starting from a 
random (scrambled) combination. The idea behind this algorithm follows the idea of achieving an adjacency matrix that matches
the adjacency matrix of reference graph. The algorithm achieves that by swapping rows and columns of the combinational graphs 
adjacency matrix. 
