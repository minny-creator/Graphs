# Graphs
/Minimum_spanning_tree_kruskal_algo.c
/Minimum_spanning_tree_prim_algo.c
/directed_dijkstra_algo.c
/undirected_BFS_trav_algo.c
/
all about directed and undirected graphs and finding minimum spanning tree.    
there can be small changes to prim's algorithm(i.e..modified prim) which makes prim's to run better than earlier(but not a drastic change in time complexity).     
there also can be a small modification to Dijkstra's algorithm in a similar way as modification can be done to a prim's as discussed above
# DIAMETER of tree(undirected weighted graph)
/diameter_of_tree.c
/optimised_diameter_code.c
/
diameter of the tree is nothing but a longest path .
In other words,when we take all paths between all pairs of nodes in undirected weighted graph ,then there will be some path whose sum of weights is the largest of all which we are now calling as DIAMETER of the tree.
both diameter_of_tree.c and optimised_diameter_code.c are almost same and have same asymptotic time complexity but have different empirical time complexities.
optimised code has less empirical time complexity than normal code.
because of extra code designed in normal file,these differences exists.
that extra code is to calculate levels of leaf nodes in the tree.
the levels of leaf nodes in the tree can be calculated parallelly when building the tree using adjacent list of nodes information but with extra space complexities.
on the other hand the levels can be calculated after building the whole tree by traversing the tree again,which takes extra timebut less space time complexity.
the first method was implemented in optimised code and second method was implemented in normal code.
