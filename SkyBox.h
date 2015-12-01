#pragma once
#include "Texture.h"
class SkyBox
{
public:
	SkyBox(float);
	~SkyBox();
	void draw();
	Texture left, right, front, back, top, base;
	float size;
	void load();
};

