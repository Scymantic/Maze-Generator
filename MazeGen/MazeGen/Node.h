//Node class
//Adrian Barberis
//COSC 3020 
//Nov 8 2016

#ifndef Node_h
#define Node_h

class Node
{
public:
	Node()
	{
		_data = 0;
		_rank = 0;
		_parent = this;
	}

	Node(const Node* n)
	{
		this->_data = n->_data;
		this->_rank = n->_rank;
		this->_parent = n->_parent;
	}

	//+----------------------+
	//|      Modifiers       |
	//+----------------------+

	void setData(int x)
	{
		_data = x;
	}

	void incrRank()
	{
		_rank++;
	}
	
	void setParent(Node* n)
	{
		_parent = n;
	}


	//+----------------------+
	//|      Accessors       |
	//+----------------------+

	int getData()
	{
		return _data;
	}

	int getRank()
	{
		return _rank;
	}

	Node* getParent()
	{
		return _parent;
	}
	void setAdj(std::vector<int> vec)
	{
		_adj = vec;
	}
	std::vector<int> getAdj()
	{
		return _adj;
	}


private:
	int _data;
	int _rank;
	Node* _parent;
	std::vector<int> _adj;
};


#endif /* Node_h */
