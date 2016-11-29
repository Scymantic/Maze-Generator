//
//  Maze.h
//  3020Project_2
//
//  Created by Adrian Barberis on 10/7/16.
//  Copyright © 2016 Adrian Barberis. All rights reserved.
//

#ifndef Maze_h
#define Maze_h

// Generate a Maze

#include<vector>
#include<iostream>
#include<list>
#include<algorithm>
#include<map>
#include"DisjointSet.h"
#include"RandomUtilities.h"




class Maze
{
public:


	Maze(int length, int width)
	{
		_length = length;
		_width = width;
		randomizeSeed();

		for (int i = 0; i < length*width; i++)
		{
			_forest.push_back(new DJSet(i));
		}
	}

	//+----------------------+
	//|      Modifiers       |
	//+----------------------+


	//Generates a maze
	//Loops until the end Room (i.e. last DJSet in forest) is connected with the start room (i.e. first DJSet in forest)
	void build()
	{
		fillAdjacencyLists();
		int i = 0;
		while (!_forest[0]->find(_forest[_forest.size()-1]))
		{
			if (i > _forest.size()-1)
			{
				i = 0;
			}
			int sizeA = _forest[i]->getSet()->getHead()->getAdj().size();
			int rand = randInt(0, sizeA - 1);
			int adjacent = _forest[i]->getSet()->getHead()->getAdj()[rand];
			knockWall(i, adjacent);
			i++;
		}
	



	}

	//check if Sets are connected before merging
	//If so do nothing
	void knockWall(int i, int j)
	{
		if (!_forest[i]->find(_forest[j]))
		{
			DJSet::unite(_forest[i], _forest[j]);
		}
	}


	//BEGIN fillAdjacencyList() ToolBox
	//_____________________________________________________________________


	//Determine the Nodes that would be adjacent to each Node if the mase were to be written out as a grid
	//    i.e.
	//            The rooms (Nodes; in other words DJSets) that are adjacent to Set 0   (i.e. the top left corner of the maze)
	//			  Are the next Right and the Bottom left or rather they are Set (Room) 1  &&  Set (Room) 3
	// Store these adjacency numbers in the adjacency set of each Node.
	void fillAdjacencyLists()
	{

		for (int i = 0; i < _forest.size(); i++)
		{
			std::vector<int> temp;
			if (isTLCorner(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isTRCorner(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isTopEdge(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isLEdge(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isCenter(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isBLCorner(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isBRCorner(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isREdge(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
			else if (isBotEdge(_forest[i]->getSet()->getHead()))
			{
				temp.push_back(_forest[i]->getSet()->getHead()->getData() + 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - 1);
				temp.push_back(_forest[i]->getSet()->getHead()->getData() - _length);
				_forest[i]->getSet()->getHead()->setAdj(temp);
			}
		}
	}

	//The following methods are for use by fillAdjacecncyList()
	//The simply check the location relative to a x,y, grid of each node in the forest
	//The method then returns a boolean value based on whether or not the Node is a TopLeft Corner or Simply a TopEdge or a Center and so on.

	bool isLEdge(Node* n)
	{

		if (n->getData() % _length == 0)
		{
			return true;
		}
		return false;
	}

	bool isREdge(Node* n)
	{
		if (n->getData() % _length == _length - 1)
		{
			return true;
		}
		return false;
	}

	bool isTopEdge(Node* n)
	{
		if (n->getData() < _length)
		{
			return true;
		}
		return false;
	}

	bool isBotEdge(Node* n)
	{
		if (n->getData() >= _length*(_width - 1))
		{
			return true;
		}
		return false;
	}

	bool isTRCorner(Node* n)
	{
		if (isREdge(n) && isTopEdge(n))
		{
			return true;
		}
		return false;
	}

	bool isTLCorner(Node* n)
	{
		if (isLEdge(n) && isTopEdge(n))
		{
			return true;
		}
		return false;
	}

	bool isBLCorner(Node* n)
	{
		if (isLEdge(n) && isBotEdge(n))
		{
			return true;
		}
		return false;
	}

	bool isBRCorner(Node* n)
	{
		if (isREdge(n) && isBotEdge(n))
		{
			return true;
		}
		return false;
	}

	bool isCenter(Node* n)
	{
		if (!isREdge(n) && !isLEdge(n) && !isBotEdge(n) && !isTopEdge(n))
		{
			return true;
		}
		return false;
	}


	bool isConnected(DJSet* one, DJSet* two)
	{
		if (one->find(two) || two->find(one))
		{
			return true;
		}
		return false;
	}

	//End methods used by fillAdjacencyList()

	//________________________________________________________________________________


	//+----------------------+
	//|      Accessors       |
	//+----------------------+


	std::vector<DJSet*> getForest()
	{
		return _forest;
	}


	

private:
	std::vector<DJSet*> _forest;
	std::vector<std::pair<int,int>> tried;
	int _length;
	int _width;
};



#endif /* Maze_h */
