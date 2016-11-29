//
//  DoubleLinkedList.h
//  3020Project_2
//
//  Created by Adrian Barberis on 10/9/16.
//  Copyright © 2016 Adrian Barberis. All rights reserved.
//

#ifndef ParentTree_h
#define ParentTree_h

#include<iostream>
#include"Node.h"


//+----------------------------------------------------------------------------------------------------------+
//|    the findN() and  merge() operations for the Parent Pointer Tree Data struc.							 |
//|	   and by extension the same methods in the DJSet class have amortized runnning cost					 |
//|    equal to some constant which is the inverse of the Ackerman function                                  |
//|    (see  Wikipedia:  Disjoint Set Data Structure)														 |
//|    Thus each subsequent operation on the tree is done faster.											 |
//|    However du to the actual creatioon of the Maze in the Maze class this might not seem super apperant   |
//+----------------------------------------------------------------------------------------------------------+





class PPTree
{
public:

	PPTree()
	{
		//_children.push_back(this);
	}

	//+----------------------+
	//|      Modifiers       |
	//+----------------------+



	//Recursively travels up Tree. 
	//!!!! As it does so it automatically FLATTENS OUT THE TREE STRUCT. !!!!
	//This means that a tree which originally looked like   a->b->d->e  will now look like
	//   a->e   b->e   d->e   since they all share the same overarching parent in the end.
	Node* findN(Node* n)
	{
		if (n->getParent() != n)
		{
			n->setParent(findN(n->getParent()));
		}
		return n->getParent();
	}



	/*Merges two trees together 
	0
			!!!!!   Y is the new PARENT X is Y's new CHILD   !!!!!!
	0
		If the overarching parent of the two trees is the same it returns
			!!!!!  If not it attempts to optimize later calculations by MERGING TREES BY RANK   !!!!!
	0
	 This allows us decrease the depth of the tree at the same time increaseing the width making later traversals faster
	0
	0
	  It also adds the PARENT TREE's CHILDREN PPTrees to an array to make later look up easy 
	  ONLY IF BOTH RANKS ARE SAME does the code INCREASE rank
	0
	0
	  Note that you cant really have loopy trees due to the fact that union(x,y) and union(y,x) are the same operation because of the way find() works
		 For example:
	0
	
	  Let's say I have    3 Parent is 5   &&  1 Parent is 3  what I really have is:   3 Parent is 5   &&   1 Parent is 5
	  so lets say I make a new set (6):     6 Parent is 6   because it is a singleton
		now I want to unite/merge   6 & 1  i.e  unite(6,1)   well that mean that by the end of it I will have:   3 Parent is 5   &&   1 Parent is 5  &&   6 Parent is 5
		therefore doing the operation:   unite(1,6)  to form a loop is pointless  since both 1 and 6 already have the same parent
	0
	0

	 */
	void merge(PPTree* x, PPTree* y)
	{
		Node* xRoot = findN(&x->_head);
		Node* yRoot = findN(&y->_head);

		if (xRoot == yRoot){ return; }

		if (xRoot->getRank() < yRoot->getRank())
		{
			xRoot->setParent(yRoot);

			//this add the PPTree X to the array of PPTrees in Y 
			//You are using the ORIGINAL TREES PASSED INTO THE FUNCTION NOT THE "PARENT" TREE OF X/Y
			y->_children.push_back(x);
		}
		else if (xRoot->getRank() > yRoot->getRank())
		{
			yRoot->setParent(xRoot);
			x->_children.push_back(y);
		}
		else
		{
			yRoot->setParent(xRoot);
			x->_children.push_back(y);
			xRoot->incrRank();
		}

	}


	//+----------------------+
	//|      Accessors       |
	//+----------------------+

	Node* getHead()
	{
		return &_head;
	}

	std::vector<PPTree*> getChildren()
	{
		return _children;
	}

	bool findT(PPTree* tree)
	{
		if (std::find(this->_children.begin(), this->_children.end(), tree) != this->_children.end())
		{
			return true;
		}
		return false;
	}


private:
	std::vector<PPTree*> _children;
	Node _head;
};





#endif /* ParentTree_h */
