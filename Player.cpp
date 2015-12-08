#include "Player.h"

Player::Player()
{
	position = new Vector3(0, 0, 30);
	this->debug = false;
    this->collisionDetected = false;

    this->halfSize = 3;
}

// debug: bounding boxes
void Player::draw(){
	glPushMatrix();

	glTranslatef((*position)[0], (*position)[1], (*position)[2]);
    if (debug){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);

		// Draw front face:
        if( !collisionDetected )
            glColor3f(0.0, 1.0, 0.0);  // green if no collision
        else
            glColor3f(1.0, 0.0, 0.0);  // red if collision
        
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, halfSize);
		glVertex3f(halfSize, -halfSize, halfSize);
		glVertex3f(-halfSize, -halfSize, halfSize);

		// Draw left side:
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-halfSize, halfSize, halfSize);
		glVertex3f(-halfSize, halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, halfSize);

		// Draw right side:
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, halfSize);

		// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, -halfSize);

		// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, -halfSize);
		glVertex3f(-halfSize, halfSize, -halfSize);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-halfSize, -halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, halfSize);
		glVertex3f(-halfSize, -halfSize, halfSize);

		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glColor3f(.6, .6, .6);
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

void Player::setCollisionDetected(bool b) {
    this->collisionDetected = b;
}

Player::~Player()
{
}
