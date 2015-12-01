#pragma once
#include <set>
#include "Cells.h"
#include <vector>
class Maze
{
public:
	Maze(int);
	std::set<Cells*> setMatch(Cells*);
	std::vector<std::set<Cells*>> *sets = new std::vector<std::set<Cells*>>();
	void draw();
	~Maze();
};

