#include "Player.h"


Player::Player()
{
	position = new Vector3(0, 0, 30);
}

void Player::draw(){
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glTranslatef((*position)[0], (*position)[1], (*position)[2]);
	glutSolidSphere(3, 50, 50);
	glDisable(GL_CULL_FACE);
	glPopMatrix();
}

void Player::move(Vector3 e){
	position->set(e[0],e[1],e[2]);
}



Player::~Player()
{
}
