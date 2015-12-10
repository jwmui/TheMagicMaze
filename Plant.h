#pragma once
#include <string>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <vector>
#include <stack>
#include "Vector3.h"

class Plant
{
public:
    Plant( float, float, float, int, float, float, float,
          float, float,
          float, float );
    ~Plant();
    
    //float x, y, z;
    int n;
    std::string s;
    float lengthF, plusAngle, minusAngle, andAngle, caratAngle, backslashAngle, forwardslashAngle;
    
    std::vector<Vector3> drawVector;
    std::stack<std::pair<Vector3,Vector3>> prevStack;
    // direction, position
    
    void draw();
    
    Vector3 currDirection;
    Vector3 currPosition;
    
    Vector3 prevDirection;
    Vector3 prevPosition;

};

