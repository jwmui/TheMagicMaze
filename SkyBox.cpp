#include "SkyBox.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

SkyBox::SkyBox(float size)
{
	this->size = size;
}


SkyBox::~SkyBox()
{
}

void SkyBox::draw(){
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	float halfSize = size / 2.0;

	// Draw back face:
	glColor3f(1.0, 1.0, 1.0);
	back.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	back.unbind();

	// Draw left side:
	glColor3f(1.0, 1.0, 1.0);
	left.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glEnd();
	left.unbind();

	// Draw right side:
	glColor3f(1.0, 1.0, 1.0);
	right.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, halfSize);	
	glEnd();
	right.unbind();

	// Draw front face:
	glColor3f(1.0, 1.0, 1.0);
	front.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, -halfSize);
	glEnd();
	front.unbind();

	// Draw top side:
	glColor3f(1.0, 1.0, 1.0);
	top.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, halfSize);
	glEnd();
	top.unbind();

	// Draw bottom side:
	glColor3f(1.0, 1.0, 1.0);
	base.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glEnd();
	base.unbind();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void SkyBox::load(){
	left = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_left.ppm");
	right = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_right.ppm");
	back = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_back.ppm");
	front = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_front.ppm");
	top = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_top.ppm");
	base = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/Skybox_Water222_base.ppm");
}
