#pragma once
#include "utils.h"

class MapGenerator
{
private:
    Map map;

    bool isPointInvalid(char point);
    void drawMaze();
    void drawEnemy();
    void drawPlayer();
    void fillWithCandyAndWall();

public:
    MapGenerator(Map map);    
    void generateMap();
    
};