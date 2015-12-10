#include "Maze.h"
#include <iostream>
#include "Wall.h"
#include "Player.h"

const int size = 10;
Cells *grid[size][size];

Maze::Maze(int seed)
{
	
    this->seed = seed;
    regenerate(this->seed);
}

void Maze::regenerate(int seed)
{
    this->seed = seed;
    //std::cout << "seed: " << seed<< "\n";
    walls = new std::vector<Wall *>();
    plants = new std::vector<Plant *>();
    sets = new std::vector<std::set<Cells*>>();
    
	srand(seed);
	int numSets = size*size;
	//std::cout << "Init";
	
    // Kruskal's maze generation algorithm
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
		//std::cout << cur->x << " " << cur->y << " ";
		int dir = rand() % 4;
		//std::cout << dir;
		switch (dir){

		case 0:
			//std::cout << "left\n";
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
			//std::cout << "right\n";
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
			//std::cout << "top\n";
			if (cur->frontW && cur->y != 0){
				Cells *neigh = grid[cur->x][cur->y - 1];
				std::set<Cells*> *c1 = setMatch(neigh);
				std::set<Cells*> *c2 = setMatch(cur);
				if (c1 != c2){
					cur->frontW = 0;
					neigh->backW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;
		case 3:
			//std::cout << "bottom\n";
			if (cur->backW && cur->y != size - 1){
				Cells *neigh = grid[cur->x][cur->y + 1];
				std::set<Cells*>* c1 = setMatch(neigh);
				std::set<Cells*>* c2 = setMatch(cur);
				if (c1 != c2){
					cur->backW = 0;
					neigh->frontW = 0;
					c1->insert(c2->begin(), c2->end());
					c2->clear();
					numSets--;
				}
			}
			break;

		}

	}

	//set entrance and exit
	grid[0][0]->frontW = 0;
	grid[size - 1][size - 1]->backW = 0;
    
    int numTrees = 0;
    
    // create walls data structure HERE
    //j = y and i = x (x is col y is row)
    for (int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            Cells *cur = grid[i][j];
            //(i*20.0, 0.0, j*-20.0);
            //drawCube(cur->leftW,cur->rightW,cur->frontW,cur->backW);
            // create draw from data structures of walls
            // split this into necessary drawWall()
            
            // using this criteria for plants. if has three walls. bc then not on path.
            int numWalls = 0;
            if(cur->leftW) numWalls++;
            if(cur->rightW) numWalls++;
            if(cur->backW) numWalls++;
            if(cur->frontW) numWalls++;
            float halfSize = 10;
            
            // let's limit the number of trees to 3 for fast rendering. but random.
            if(numWalls == 3 && numTrees < 3) {
                Plant * plant = new Plant(i*20.0, 0.0-halfSize, j*-20.0, 6);
                plants->push_back(plant);
                numTrees++;
            }
                
            Wall * leftW = new Wall(cur->leftW, i*20.0, 0.0, j*-20.0, LEFT);
            walls->push_back(leftW);

            if(i == size-1) {
                Wall * rightW = new Wall(cur->rightW, i*20.0, 0.0, j*-20.0, RIGHT); //
                walls->push_back(rightW);
            }
            else {
                Wall * rightW = new Wall(NULL, i*20.0, 0.0, j*-20.0, RIGHT); //
                walls->push_back(rightW);
            }

            Wall * frontW = new Wall(cur->frontW, i*20.0, 0.0, j*-20.0, FRONT); //
            walls->push_back(frontW);
            
            if(j == size-1) {
                Wall * backW = new Wall(cur->backW, i*20.0, 0.0, j*-20.0, BACK);
                walls->push_back(backW);
            }
            else {
                Wall * backW = new Wall(NULL, i*20.0, 0.0, j*-20.0, BACK);
                walls->push_back(backW);
            }

        }
        
        //std::cout << "\n";
    }
}

std::set<Cells*>* Maze::setMatch(Cells *toFind){
	for (std::vector<std::set<Cells*>>::iterator it = sets->begin(); it != sets->end(); ++it) {
		for (std::set<Cells*>::iterator it1 = it->begin(); it1 != it->end(); it1++){
			if (toFind == *it1){
				return &(*it);
			}
		}
	}
    return nullptr; // shall not be reached
}

void Maze::draw(){
	
	//j = y and i = x (x is col, y is row)
	for (int j = 0; j < size; j++){
		for(int i = 0; i < size; i++){
			Cells *cur = grid[i][j];
			glPushMatrix();
			glTranslatef(i*20.0, 0.0, j*-20.0);
			//drawCube(cur->leftW,cur->rightW,cur->frontW,cur->backW);
            // split this into necessary drawWall()
            int ind = j*size*4 + i*4;
            walls->at(ind+0)->draw(debug);
            walls->at(ind+1)->draw(debug);
            walls->at(ind+2)->draw(debug);
            walls->at(ind+3)->draw(debug);

			float halfSize = 10;
			floorTex.bind();
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2f(0, 0);
			glVertex3f(-halfSize, -halfSize, -halfSize);
			glTexCoord2f(1, 0);
			glVertex3f(halfSize, -halfSize, -halfSize);
			glTexCoord2f(1, 1);
			glVertex3f(halfSize, -halfSize, halfSize);
			glTexCoord2f(0, 1);
			glVertex3f(-halfSize, -halfSize, halfSize);
			glEnd();
			floorTex.unbind();

			glPopMatrix();
		}
		
        for (std::vector<Plant *>::iterator it = plants->begin(); it != plants->end(); ++it) {
            //glPushMatrix();
            Plant * p = *it;
            //glTranslatef(p->currPosition[0], p->currPosition[1], p->currPosition[2]);
            //p->currPosition.print("");
            p->draw();
            //glPopMatrix();
        }
        
		//std::cout << "\n";
	}

}

Vector3 Maze::doCollisionDetection(Vector3 position, Player * player) {
    player->setCollisionDetected(false);
    
    for(std::vector<Wall*>::iterator it = walls->begin(); it != walls->end(); ++it) {
        Wall * currWall = *it;
        currWall->setCollisionDetected(false);
        
        if(currWall->valid == 0) continue;  // nonexistent walls don't count
        
        // are these right coordinates? TODO
        
        float x1 = position[0] - player->halfSize;
        float x2 = position[0] + player->halfSize;
        float z1 = position[2] - player->halfSize;
        float z2 = position[2] + player->halfSize;
        
        float x3 = currWall->x3;
        float x4 = currWall->x4;
        float z3 = currWall->z3;
        float z4 = currWall->z4;
        
        bool intersectX = false;
        bool intersectZ = false;
        
        int x = position[0];
        float z = position[2];
        
        // WEIRD BC THERE'S TWO WALLS BEING GENERATED. -- FIXed
        if( (x3 < x1 && x1 < x4) ||
           (x1 < x3 && x4 < x2) ||
           (x3 < x2 && x2 < x4) ) {
            
            intersectX = true;
            
            // prevents walking thru walls
            // if player is going in the left direction
            if((*player->position)[0] > position[0])
                x = x4+player->halfSize;
            // if player is going in the right direction
            else if((*player->position)[0] < position[0])
                x = x3-player->halfSize;
        }
        
        if( (z3 < z1 && z1 < z4) ||
           (z1 < z3 && z4 < z2) ||
           (z3 < z2 && z2 < z4) ) {
            intersectZ = true;
            
            // prevents walking thru walls
            // if player is going in the back direction
            if((*player->position)[2] > position[2])
                z = z4+player->halfSize;
            // if player is going in the forward direction
            else if((*player->position)[2] < position[2])
                z = z3-player->halfSize;
        }
        
        
        if(intersectX && intersectZ) {
            player->setCollisionDetected(true);
            currWall->setCollisionDetected(true);
            
            /*if(x != position[0]) {
                //std::cout << "new x: " << x << "\n";
                //std::cout << "wall: " << x3 << " " << x4 << "\n\n";
            }*/
            if(!debug) {
                position.set(x, position[1], z);
            }
            
            
        }
    }
    
    return position;
}

Maze::~Maze()
{
}

void Maze::togDebug(){
    this->debug = !this->debug;
}

void Maze::load(){
	floorTex = Texture("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/stonefloor.ppm");
}