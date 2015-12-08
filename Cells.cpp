#include "Cells.h"


Cells::Cells(int leftW, int rightW, int topW, int bottomW, int x, int y)
{
	this->leftW = leftW;
	this->rightW = rightW;
	this->frontW = topW;
	this->backW = bottomW;
	this->x = x;
	this->y = y;
}
Cells::Cells(){

}


Cells::~Cells()
{
}
