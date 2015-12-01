#pragma once
#include <set>
#include "Cells.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Maze
{
public:
	Maze(int);
	std::set<Cells*>* setMatch(Cells*);
	std::vector<std::set<Cells*>> *sets = new std::vector<std::set<Cells*>>();
	void draw();
	void drawCube(int,int,int,int);
	~Maze();
};

