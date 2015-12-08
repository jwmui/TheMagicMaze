#pragma once
#include <set>
#include "Cells.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include "Wall.h"
#include "Player.h"

class Maze
{
public:
	Maze(int);
	std::set<Cells*>* setMatch(Cells*);
	std::vector<std::set<Cells*>> *sets = new std::vector<std::set<Cells*>>();
	void draw();
	//void drawCube(int,int,int,int);
	~Maze();
    
    std::vector<Wall *>* walls = new std::vector<Wall *>();
    
    int LEFT=0;  // also defined in Wall.h be consistent
    int RIGHT=1;
    int FRONT=2;
    int BACK=3;
    
    void togDebug();
    bool debug;
    
    // passes in desired Vector3 position. returns allowed Vector3 position
    // do we need to show boxes actually intersecting???
    Vector3 doCollisionDetection(Vector3, Player *);
};

