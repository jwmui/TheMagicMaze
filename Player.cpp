#include "Player.h"


Player::Player()
{
	position = new Vector3(0, 0, 30);
	this->debug = false;
}

void Player::draw(){
	glPushMatrix();

	glTranslatef((*position)[0], (*position)[1], (*position)[2]);
	if (debug){
		glBegin(GL_LINES);
		//front bottom
		glVertex3f(-3, -3, -3);
		glVertex3f(3, -3, -3);

		//front top
		glVertex3f(-3, 3, -3);
		glVertex3f(3, 3, -3);

		//front left
		glVertex3f(-3, -3, -3);
		glVertex3f(-3, 3, -3);

		//front right
		glVertex3f(3, -3, -3);
		glVertex3f(3, 3, -3);

		//back bottom
		glVertex3f(-3, -3, 3);
		glVertex3f(3, -3, 3);

		//back top
		glVertex3f(-3, 3, 3);
		glVertex3f(3, 3, 3);

		//back left
		glVertex3f(-3, -3, 3);
		glVertex3f(-3, 3, 3);

		//back right
		glVertex3f(3, -3, 3);
		glVertex3f(3, 3, 3);

		//top left
		glVertex3f(-3, 3, 3);
		glVertex3f(-3, 3, -3);

		//top right
		glVertex3f(3, 3, 3);
		glVertex3f(3, 3, -3);

		//bottom left
		glVertex3f(-3, -3, 3);
		glVertex3f(-3, -3, -3);

		//bottom right
		glVertex3f(3, -3, 3);
		glVertex3f(3, -3, -3);

		glEnd();
	}
	glEnable(GL_CULL_FACE);
	glutSolidSphere(3, 50, 50);
	glDisable(GL_CULL_FACE);
	glPopMatrix();
}

void Player::move(Vector3 e){
	position->set(e[0],e[1],e[2]);
}

void Player::togDebug(){
	this->debug = !this->debug;
}



Player::~Player()
{
}
