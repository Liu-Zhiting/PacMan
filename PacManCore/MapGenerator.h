#pragma once
#include "utils.h"

class MapGenerator
{
private:
	int a, b;
	int left_up, left_down, right_up, right_down;
	int* data;

	bool isPointInvalid(int point);

	void drawMaze();

	void drawEnemyAtCenter();

	void fillWithCandyAndWall();

public:
	MapGenerator(int a, int b, int* data);

	

	void getNewMap();

#ifdef DEBUG
	void printData();
#endif // DEBUG

	
};