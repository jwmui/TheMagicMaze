#pragma once
class Cells
{
public:
	Cells(int leftW, int rightW, int frontW, int backW, int x, int y);
	Cells();
	~Cells();
	//0 if wall does not exist, 1 if it does
	int leftW, rightW, frontW, backW, x, y;
};

