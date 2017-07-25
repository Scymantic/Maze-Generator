# Maze-Generator
Generates a maze of size L*W

Adrian Barberis
Tuesday Nov 29, 2016 3:44PM

**Requires latest version of c++11 or latest version (there is a for each loop)**
**The compiler may wine about casting in the RandomUtilities.h file this will probably not matter if using c++11 or later but if it does simply do what the error tells you to do ¯\_(ツ)_/¯**

This was originally done as a University homework for Thomas Bailey at University of Wyoming.

This program uses the Disjoint set Data structure to generate the maze specifically it uses a disjoint set Forest.
If there is no wall between 2 "rooms" (aka nodes) then one node is the child of the other or rather the 
Nodes in the forest are connected.

The output for this program isnt really usable beacause I have not made a print() function which prints a visual representation
of the maze instead it just prints all the nodes and all the children of said nodes from this one can fairly easily draw the maze

As it is it's really just an excersize but it could be adapted to other things quite easily

For AMA or Questions:

  14abarberis@gmail.com
