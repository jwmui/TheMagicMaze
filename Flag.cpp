#include "Flag.h"

Flag::Flag(BezierCurve* c0, BezierCurve* c1, BezierCurve* c2, BezierCurve* c3, std::vector<BezierCurve*> cV, std::vector<BezierCurve*> cH)
{
	this->c0 = c0;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->curvesV = cV;
	this->curvesH = cH;
	temp = c0;
}


Flag::~Flag()
{
}

void Flag::draw(){
	//glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/*
	for (int i = 0; i < 100; i++){
		q0 = (*c0).times[i];
		q1 = (*c1).times[i];
		q2 = (*c2).times[i];
		q3 = (*c3).times[i];
		r0 = (*c0).newPoint((i*.01) + delta);
		r1 = (*c1).newPoint((i*.01) + delta);
		r2 = (*c2).newPoint((i*.01) + delta);
		r3 = (*c3).newPoint((i*.01) + delta);
		u0 = temp.newPoint((i + 1) * 0.01, q0, q1, q2, q3);
		u1 = temp.newPoint(((i + 1) * 0.01) + delta, q0, q1, q2, q3);
		tanU = u1 - u0;
		v0 = temp.newPoint((i + 1) * 0.01, r0, r1, r2, r3);
		tanV = v0 - u0;
		tanU = tanU.normalize();
		tanV = tanV.normalize;
		normal = tanU.cross(tanV);
	}*/
	glDisable(GL_CULL_FACE);
	glColor3f(1.0, 1.0, 1.0);
	logo.bind();
	shaders.bind();
	for (int v = 0; v < 100; v++){
		for (int h = 0; h < 100; h++){

			//Calc Normals
			q0 = (*c0).times[v];
			q1 = (*c1).times[v];
			q2 = (*c2).times[v];
			q3 = (*c3).times[v];
			r0 = (*c0).newPoint((v*.01) + delta);
			r1 = (*c1).newPoint((v*.01) + delta);
			r2 = (*c2).newPoint((v*.01) + delta);
			r3 = (*c3).newPoint((v*.01) + delta);
			u0 = (*temp).newPoint((v + 1) * 0.01, q0, q1, q2, q3);
			u1 = (*temp).newPoint(((v + 1) * 0.01) + delta, q0, q1, q2, q3);
			tanU = u1 - u0;
			v0 = (*temp).newPoint((v + 1) * 0.01, r0, r1, r2, r3);
			tanV = v0 - u0;
			tanU = tanU.normalize();
			tanV = tanV.normalize();
			normal = tanU.cross(tanV);
	
			glBegin(GL_QUADS);
			
			//glNormal3f(0.0, 0.0, 1.0);
			glNormal3f(-normal[0], -normal[1], -normal[2]);
			glTexCoord2f(h * 0.01,v * 0.01);
			//glTexCoord2f(0, 0);
			glVertex3f(curvesH.at(h)->times[v][0], curvesH.at(h)->times[v][1], curvesH.at(h)->times[v][2]);
			glTexCoord2f((h + 1) * 0.01, v * 0.01);
			//glTexCoord2f(1, 0);
			glVertex3f(curvesH.at(h+1)->times[v][0], curvesH.at(h+1)->times[v][1], curvesH.at(h+1)->times[v][2]);
			glTexCoord2f((h + 1) * 0.01, 0 + (v + 1) * 0.01);
			//glTexCoord2f(1, 1);
			glVertex3f(curvesH.at(h + 1)->times[v+1][0], curvesH.at(h + 1)->times[v+1][1], curvesH.at(h + 1)->times[v+1][2]);
			glTexCoord2f(0 + (h * 0.01), (v + 1) * 0.01);
			//glTexCoord2f(0, 1);
			glVertex3f(curvesH.at(h)->times[v+1][0], curvesH.at(h)->times[v+1][1], curvesH.at(h)->times[v+1][2]);



			glEnd();
			
		}
	}
	shaders.unbind();
	logo.unbind();

	glEnable(GL_CULL_FACE);


	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void Flag::load(){
	logo = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Ucsd-logo.ppm");
}
