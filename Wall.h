#pragma once
#include <string>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include "Texture.h"
#include "Globals.h"
class Wall
{
public:
    Wall(int, float, float, float, int);
	Wall();
    ~Wall();
    
    float x, y, z;
    float x3, x4, z3, z4;
    
    int face; // use one of the constants LEFT, RIGHT, FRONT, BACK
    float halfSize, thickness, halfSize1;
    int valid; // 0 invalid, 1 valid to draw

    int LEFT=0;
    int RIGHT=1;
    int FRONT=2;
    int BACK=3;
    
    void draw(bool debug);
    void drawCube();
    
    bool collisionDetected;
    void setCollisionDetected(bool);
	Texture wallTex;
	void load();
};

