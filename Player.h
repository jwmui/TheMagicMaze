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
	void togDebug();
	Vector3 *position;
	Sphere *head;
	bool debug;
};

