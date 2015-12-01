#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Light::Light() : Drawable()
{
	ambientColor = new float[]{0.1f,0.1f,0.1f,1.0f};
	diffuseColor = new float[]{0.5f, 0.5f, 0.5f, 1.0f};
	specularColor = new float[]{0.5f, 0.5f, 0.5f, 1.0f};
    
    constantAttenuation = 1.0;
    linearAttenuation = 0.0;
    quadraticAttenuation = 0.05;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor);
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
    //Add support for Linear Attenuation
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    
    //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());
    
    //Setup spotlight direction, angle, and exponent here
	glLightf(GL_LIGHT0 + bindID, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0 + bindID, GL_SPOT_EXPONENT, exponent);

	toWorld.makeTranslate(position[0], position[1], position[2]);
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}

void Light::draw(DrawData& data){
	Matrix4 transform;
	Vector3 amb;
	amb.set(1.0, 1.0, 1.0);
	material.apply(amb, amb, amb, 2.0);
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//glLoadIdentity();
	glMultMatrixf(toWorld.ptr());
	//toWorld = transform*toWorld;
	glutSolidSphere(0.1, 100, 100);

	glPopMatrix();
}
