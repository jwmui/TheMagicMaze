#pragma once
#include "Vector3.h"
#include <vector>
class BezierCurve
{
public:
	BezierCurve(std::vector<Vector3>);
	~BezierCurve();
	float getScalar(int, float);
	Vector3 newPoint(float);
	Vector3 BezierCurve::newPoint(float, Vector3, Vector3, Vector3, Vector3);
	void draw();
	float factorial(int);
	std::vector<Vector3> ctPts;
	std::vector<Vector3> times;
	Vector3 p0, p1, p2, p3;
};

