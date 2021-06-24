/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 23:06:21
 */

#pragma once
#define ENEMY_COUNT 4


#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <cstdint>

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

const int POWERED_BUFF_TIME = 20;
const int ENEMY_RESTART_TIME = 50;
const int LEN_BLOCK_LIST = 6;
const int ENEMY_SLOW_TIME = 2;

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




class Map
{

public:
    int a;
    int b;
    int left_up, left_down, right_up, right_down;
    char* data;

    Map(int a, int b, char* data);
    bool isPointInvalid(int point);

#ifdef _DEBUG
    void printData();  
    void printItem(); //■○●△▲
#endif // DEBUG   

};

