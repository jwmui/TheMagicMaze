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
    Wall(int, float, float, float, int);
    ~Wall();
    float x, y, z;
    int face; // use one of the constants LEFT, RIGHT, FRONT, BACK
    float halfSize, thickness, halfSize1;
    int valid; // 0 invalid, 1 valid to draw

    int LEFT=0;
    int RIGHT=1;
    int FRONT=2;
    int BACK=3;
    
    void draw();
};

