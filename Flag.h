#pragma once
#include "Shader.h"
#include "BezierCurve.h"
#include "Vector3.h"
#include <vector>
#include "Texture.h"



class Flag
{
public:
	Flag(BezierCurve*, BezierCurve*, BezierCurve*, BezierCurve*, std::vector<BezierCurve*>, std::vector<BezierCurve*>);
	~Flag();
	void draw();
	BezierCurve *c0,*c1, *c2, *c3;
	Vector3 q0,q1,q2,q3,r0,r1,r2,r3,u0,u1,v0, tanU, tanV, normal;
	float delta = 0.00001;
	std::vector<BezierCurve*> curvesV, curvesH;
	Texture logo;
	Shader shaders = Shader("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/VertexShader.vert", "C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/FragmentShader.frag", true);;
	void load();
	BezierCurve *temp;
};

