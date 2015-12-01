#pragma once
#include <set>
#include "Cells.h"
#include <vector>
#include <GL/freeglut.h>
class Maze
{
public:
	Maze(int);
	std::set<Cells*> Maze::setMatch(Cells*);
	std::vector<std::set<Cells*>> *sets = new std::vector<std::set<Cells*>>();
	void draw();
	~Maze();
};

