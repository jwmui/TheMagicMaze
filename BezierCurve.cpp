#include <GL/glut.h>
#include "BezierCurve.h"
#include "math.h"


BezierCurve::BezierCurve(std::vector<Vector3> ctPt)
{
	this->ctPts = ctPt;
	this->p0 = ctPt.at(0);
	this->p1 = ctPt.at(1);
	this->p2 = ctPt.at(2);
	this->p3 = ctPt.at(3);
	
}


BezierCurve::~BezierCurve()
{
	
	
	
	
}

void BezierCurve::draw(){

	glDisable(GL_CULL_FACE);
	Vector3 cPt0;
	Vector3 cPt1;
	for (float t = 0.0; t < 1.0; t += 0.01){
		//glPushMatrix();
		/*
		glBegin(GL_LINES);
		cPt0 = newPoint(t);
		this->times.push_back(cPt0);
		cPt1 = newPoint(t + 0.01);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(cPt0[0], cPt0[1], cPt0[2]);
		glVertex3f(cPt1[0], cPt1[1], cPt1[2]);
		glEnd();
		*/

		//glBegin(GL_POINTS);
		cPt0 = newPoint(t);
		this->times.push_back(cPt0);
		//glColor3f(1.0, 1.0, 1.0);
		//glVertex3f(cPt0[0], cPt0[1], cPt0[2]);
		//glEnd();
		
		//glPopMatrix();
	}
	//this->times.push_back(cPt1);
	glEnable(GL_CULL_FACE);
}

Vector3 BezierCurve::newPoint(float t){
	Vector3 result;
	float c0 = getScalar(0, t);
	float c1 = getScalar(1, t);
	float c2 = getScalar(2, t);
	float c3 = getScalar(3, t);

	result = (this->p0) * c0 + (this->p1) * c1 + (this->p2) * c2 + (this->p3) * c3;
	return result;
}

Vector3 BezierCurve::newPoint(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3){
	Vector3 result;
	float c0 = getScalar(0, t);
	float c1 = getScalar(1, t);
	float c2 = getScalar(2, t);
	float c3 = getScalar(3, t);

	result = (p0) * c0 + (p1) * c1 + (p2) * c2 + (p3) * c3;
	return result;
}

float BezierCurve::getScalar(int i, float t){
	float scalar = factorial(3) / (factorial(3 - i) * factorial(i));
	scalar = scalar * (pow(t,i)*pow((1-t), (3-i)));
	return scalar;
}

float BezierCurve::factorial(int j){
	int product = 1;
	if (j == 0){
		return 1;
	}
	for (int i = 1; i <= j; i++){
		product = product * i;
	}
	return (float)product;
}
