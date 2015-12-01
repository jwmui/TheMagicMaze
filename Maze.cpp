#include "Maze.h"
#include <iostream>

const int size = 3;
Cells *grid[size][size];

Maze::Maze(int seed)
{
	srand(seed);
	int wallsDown = 0;
	std::cout << "Init";
	

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			Cells *c = new Cells(1,1,1,1,i,j);
			grid[i][j] = c;
			std::set<Cells*> s;
			s.insert(c);
			sets->push_back(s);
		}
	}

	while(wallsDown < size*size-1){
		std::cout << "while";
		//top left = 0,0
		Cells *cur = grid[rand() % size][rand() % size];
		int dir = rand() % 4;
		//std::cout << dir;
		switch (dir){
		case 0:
			std::cout << "left";
			if (cur->leftW && cur->x != 0){
				Cells *neigh = grid[cur->x - 1][cur->y];
				std::set<Cells*> c1 = setMatch(neigh);
				std::set<Cells*> c2 = setMatch(cur);
				if (c1 != c2){
					cur->leftW = 0;
					neigh->rightW = 0;
					c1.insert(c2.begin(), c2.end());
					c2.clear();
					wallsDown++;
				}
			}
			break;
		case 1:
			std::cout << "right";
			if(cur->rightW && cur->x != size - 1){
				Cells *neigh = grid[cur->x + 1][cur->y];
				std::set<Cells*> c1 = setMatch(neigh);
				std::set<Cells*> c2 = setMatch(cur);
				if (c1 != c2){
					cur->rightW = 0;
					neigh->leftW = 0;
					c1.insert(c2.begin(), c2.end());
					c2.clear();
					wallsDown++;
				}
			}
			break;
		case 2:
			std::cout << "top";
			if(cur->topW && cur->y != 0){
				Cells *neigh = grid[cur->x][cur->y - 1];
				std::set<Cells*> c1 = setMatch(neigh);
				std::set<Cells*> c2 = setMatch(cur);
				if (c1 != c2){
					cur->topW = 0;
					neigh->bottomW = 0;
					c1.insert(c2.begin(), c2.end());
					c2.clear();
					wallsDown++;
				}
			}
			break;
		case 3:
			std::cout << "bottom";
			if (cur->bottomW && cur->y != size - 1){
				Cells *neigh = grid[cur->x][cur->y + 1];
				std::set<Cells*> c1 = setMatch(neigh);
				std::set<Cells*> c2 = setMatch(cur);
				if (c1 != c2){
					cur->bottomW = 0;
					neigh->topW = 0;
					c1.insert(c2.begin(), c2.end());
					c2.clear();

				}
			}
			break;
			
		}
		
	}
}

std::set<Cells*> Maze::setMatch(Cells *toFind){
	for (std::vector<std::set<Cells*>>::iterator it = sets->begin(); it != sets->end(); ++it) {
		for (std::set<Cells*>::iterator it1 = it->begin(); it1 != it->end(); it1++){
			if (toFind == *it1){
				return (*it);
			}
		}
	}
    std::set<Cells*> s;
    return s; // shall not be reached
}

void Maze::draw(){
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if (grid[i][j]->topW == 1){
				std::cout<<" _ ";
			}
			else{
				std::cout << "    ";
			}
		}
		std::cout << "\n";
		for (int j = 0; j < size; j++){
			if (grid[i][j]->leftW == 1){
				std::cout << "|";
			}
			else{
				std::cout << " ";
			}
			if (grid[i][j]->bottomW == 1){
				std::cout << "_";
			}
			else{
				std::cout << "  ";
			}
			if (grid[i][j]->rightW == 1){
				std::cout << "|";
			}
			else{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

Maze::~Maze()
{
}
