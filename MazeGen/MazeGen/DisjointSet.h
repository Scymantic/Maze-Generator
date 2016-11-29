//
//  DisjointSet.h
//  3020Project_2
//
//  Created by Adrian Barberis on 10/9/16.
//  Copyright © 2016 Adrian Barberis. All rights reserved.
//

#ifndef DisjointSet_h
#define DisjointSet_h

#include"ParentTree.h"

class DJSet
{
public:

	//DJSet(){}

	DJSet(int data)
	{
		_set.getHead()->setData(data);
	}


	//+----------------------+
	//|      Modifiers       |
	//+----------------------+

	//Returns TRUE ONLY IF:  After merge() operation:    BOTH   Y    &&    X    have same OVERARCHING PARENT
	//  The bool return value could easily be removed in favor of a simple void thus making this operation a bit faster by removing 
	//   the find operation however it it may infact be useful and simply  doing   a unite() and then find() seperately costs about as much as doing 
	//    them in the same function call.
	static bool unite(DJSet* x, DJSet* y)
	{
		x->_set.merge(&x->_set, &y->_set);
		//if (y->find(x))
		//{
			//return true;
		//}
		return true;
	}



	//+----------------------+
	//|      Accessors       |
	//+----------------------+


	//Returns TRUE ONLY IF:  this DJSet->_head has SAME OVERARCHING PARENT as DJSet Y->_head
	bool find(DJSet* y)
	{
		Node* yRoot = y->_set.findN(y->_set.getHead());
		Node* xRoot = this->_set.findN(this->_set.getHead());
		if (yRoot == xRoot)
		{
			return true;
		}
		return false;
	}



	PPTree* getSet()
	{
		return &_set;
	}



	void print()
	{
		std::cout << "Disjoint Set   [ ";
		std::cout << _set.getHead()->getData() << " ]   Children Are ----> ";

		if (_set.getChildren().size() == 0)
		{
			std::cout << "NONE" << std::endl;
		}

		for (int i = 0; i < _set.getChildren().size(); i++)
		{
			std::cout << _set.getChildren()[i]->getHead()->getData();

			if (i+1 < _set.getChildren().size())
			{
				std::cout << " :: ";
			}
		}
		std::cout << std::endl << std::endl;
	}

private:
	PPTree _set;
};


#endif /* DisjointSet_h */
