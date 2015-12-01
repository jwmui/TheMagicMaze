#include "Maze.h"
#include <iostream>


const int size = 10;
Cells *grid[size][size];

Maze::Maze(int seed)
{
	srand(seed);
	int numSets = size*size;
	//std::cout << "Init";
	

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			Cells *c = new Cells(1,1,1,1,i,j);
			grid[i][j] = c;
			std::set<Cells*> s;
			s.insert(c);
			sets->push_back(s);
		}
	}

	while (numSets > 1){

		//top left = 0,0
		Cells *cur = grid[rand() % size][rand() % size];
		std::cout << cur->x << " " << cur->y << " ";
		int dir = rand() % 4;
		//std::cout << dir;
		switch (dir){

		case 0:
			std::cout << "left\n";
			if (cur->leftW && cur->x != 0){
				Cells *neigh = grid[cur->x - 1][cur->y];
				std::set<Cells*>* c1 = setMatch(neigh);
				std::set<Cells*>* c2 = setMatch(cur);
				if (c1 != c2){
					cur->leftW = 0;
					neigh->rightW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;
		case 1:
			std::cout << "right\n";
			if (cur->rightW && cur->x != size - 1){
				Cells *neigh = grid[cur->x + 1][cur->y];
				std::set<Cells*>* c1 = setMatch(neigh);
				std::set<Cells*>* c2 = setMatch(cur);
				if (c1 != c2){
					cur->rightW = 0;
					neigh->leftW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;
		case 2:
			std::cout << "top\n";
			if (cur->topW && cur->y != 0){
				Cells *neigh = grid[cur->x][cur->y - 1];
				std::set<Cells*> *c1 = setMatch(neigh);
				std::set<Cells*> *c2 = setMatch(cur);
				if (c1 != c2){
					cur->topW = 0;
					neigh->bottomW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;
		case 3:
			std::cout << "bottom\n";
			if (cur->bottomW && cur->y != size - 1){
				Cells *neigh = grid[cur->x][cur->y + 1];
				std::set<Cells*>* c1 = setMatch(neigh);
				std::set<Cells*>* c2 = setMatch(cur);
				if (c1 != c2){
					cur->bottomW = 0;
					neigh->topW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;

		}

	}

	//set entrance and exit
	grid[0][0]->topW = 0;
	grid[size - 1][size - 1]->bottomW = 0;
}

std::set<Cells*>* Maze::setMatch(Cells *toFind){
	for (std::vector<std::set<Cells*>>::iterator it = sets->begin(); it != sets->end(); ++it) {
		for (std::set<Cells*>::iterator it1 = it->begin(); it1 != it->end(); it1++){
			if (toFind == *it1){
				return &(*it);
			}
		}
	}
    std::set<Cells*> s;
    return &s; // shall not be reached
}

void Maze::draw(){
	//j = y and i = x (x is col y is row)
	for (int j = 0; j < size; j++){
		for(int i = 0; i < size; i++){
			Cells *cur = grid[i][j];
			glPushMatrix();
			glTranslatef(i*20.0, 0.0, j*-20.0);
			drawCube(cur->leftW,cur->rightW,cur->topW,cur->bottomW);
			glPopMatrix();
		}
		
		//std::cout << "\n";
	}
}

void Maze::drawCube(int left, int right, int top, int bottom){
	float halfSize = 10;

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	// Draw front (top) face:
	if (top){
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, halfSize);
		glVertex3f(halfSize, -halfSize, halfSize);
		glVertex3f(-halfSize, -halfSize, halfSize);
	}

	// Draw left side:
	if (left){
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-halfSize, halfSize, halfSize);
		glVertex3f(-halfSize, halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, halfSize);
	}

	// Draw right side:
	if (right){
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(halfSize, halfSize, halfSize);
		glVertex3f(halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, halfSize);
	}

	// Draw back (bottom) face:
	if (bottom){
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, halfSize, -halfSize);
		glVertex3f(halfSize, -halfSize, -halfSize);
		glVertex3f(-halfSize, -halfSize, -halfSize);
	}

	glEnd();
}

Maze::~Maze()
{
}
