#pragma once
class Cells
{
public:
	Cells(int leftW, int rightW, int topW, int bottomW, int x, int y);
	Cells();
	~Cells();
	//0 if wall does not exist, 1 if it does
	int leftW, rightW, topW, bottomW, x, y;
};

