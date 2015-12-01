#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Vector3 amb1, dif1, spec1;
float shine1;

Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
	amb1.set(0.5, 0.0, 0.0);
	dif1.set(0.5, 0.4, 0.4);
	spec1.set(0.7, 0.04, 0.04);
	shine1 = 0.078125;
}

void Sphere::draw(DrawData& data)
{
    //material.apply(amb1, dif1, spec1, shine1);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}


