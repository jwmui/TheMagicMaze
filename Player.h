#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Sphere.h"
#include "Vector3.h"

class Player
{
public:
	Player();
	~Player();
	void draw();
	void move(Vector3);
	Vector3 *position;
	Sphere *head;

    void togDebug();
	bool debug;
    
    bool collisionDetected;
    void setCollisionDetected(bool);
    
    float halfSize;
};

