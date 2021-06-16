#pragma once
#include "utils.h"

class MapGenerator
{
private:
    int a, b;
    int left_up, left_down, right_up, right_down;
    int* data;
    Map map;

    bool isPointInvalid(int point);
    void drawMaze();
    void drawEnemy();
    void drawPlayer();
    void fillWithCandyAndWall();

public:
    MapGenerator(Map map);    
    void generateMap();
    
};