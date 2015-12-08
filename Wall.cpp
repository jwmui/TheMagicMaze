#include "Wall.h"


Wall::Wall(bool valid,float p1, float p2, float p3, float p4, int face)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->face = face;
	this->valid = valid;
}

void Wall::draw(){
	float halfSize = 10;
	float thickness = 1.0;
	float halfSize1 = 10 + thickness;

	
}

Wall::~Wall()
{
}
