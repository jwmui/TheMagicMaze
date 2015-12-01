#pragma once
#include "Drawable.h"

class Rasterizer
{
public:
	Rasterizer(Drawable*, int);
	~Rasterizer();
	void draw(int);
	Vector3 rasterizeVertex(Vector4);
	void rasterizeTriangle(Vector3, Vector3, Vector3, Vector3, Vector3, Vector3, bool);
	void Rasterizer::setDebug(int debug1);
	void reshape(int, int);
	void loadData();	
	void setToDraw(Drawable*);
	void setScene(int);
};

