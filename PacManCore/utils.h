#pragma once
#define ENEMY_COUNT 4

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

enum EntityType {
    EMPTY,
    WALL,
    CANDY,
    CANDY_POWERED,
    PLAYER,
    PLAYER_POWERED,
    ENEMY_SIMPLE_FAST,
    ENEMY_SIMPLE_SLOW,
    ENEMY_SMART_FAST,
    ENEMY_SMART_SLOW,
    PLAYER_WITH_ENEMY
};

enum Key {
    ARROW_UP,
    ARROW_LEFT,
    ARROW_DOWN,
    ARROW_RIGHT
};

const int POWERED_BUFF_TIME = 20;
const int ENEMY_RESTART_TIME = 15;


class Map
{

public:
    int a;
    int b;
    int left_up, left_down, right_up, right_down;
    int* data;

    Map(int a, int b, int* data);
    bool isPointInvalid(int point);

#ifdef _DEBUG
    void printData();  
    void printItem(); //■○●△▲
#endif // DEBUG   

};

