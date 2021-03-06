//
//  main.cpp
//  3020Project_2
//
//  Created by Adrian Barberis on 10/7/16.
//  Group Members
//  Jackson Colter
//  Sean McConnell
//
//  Copyright © 2016 Adrian Barberis. All rights reserved.
//

#include"Maze.h"
#include"ParentTree.h"
#include"DisjointSet.h"

using namespace::std;

#include<string>

void run();

int main()
{
	
	run();

	std::string more;
	cout << " Press Y to continue N to Quit: ";
	cin >> more;
	while (more == "Y")
	{
		run();
		cout << " Press Y to continue N to Quit: ";
		cin >> more;
	}
	if (more == "N")
	{
		exit(0);
	}



	return 0;
}

void run()
{
	int length = 0;
	int width = 0;
	cout << "Please enter a Length and a Width (0 to quit): " << endl;
	cout << "L: ";
	cin >> length;

	if (length == 0)
	{
		exit(0);
	}

	cout << endl;
	cout << "W: ";
	cin >> width;

	if (width == 0)
	{
		exit(0);
	}


	Maze maze(length, width);
	maze.build();
	for each(DJSet* set in maze.getForest())
	{
		set->print();
	}
}
