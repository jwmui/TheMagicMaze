#pragma once
#include <string>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Wall
{
public:
	Wall(bool,float, float, float, float, int);
	~Wall();
	void draw();
	float p1, p2, p3, p4;
	int face;
	bool valid;
};

