/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 22:55:41
 */
#pragma once
#include "utils.h"

class MapGenerator
{
private:
    Map map;
    char difficulty;
    char typeBitmap[35] = {
        (char)0x00, (char)0x01,(char)0x05,(char)0x15,(char)0x55,
        (char)0x02,(char)0x06,(char)0x16,(char)0x56,(char)0x0A,
        (char)0x1A,(char)0x5A,(char)0x2A,(char)0x6A,(char)0xAA,
        (char)0x03,(char)0x07,(char)0x17,(char)0x57,(char)0x0B,
        (char)0x1B,(char)0x5B,(char)0x2B,(char)0x6B,(char)0xAB,
        (char)0x0F,(char)0x1F,(char)0x5F,(char)0x2F,(char)0x6F,
        (char)0xAF,(char)0x3F,(char)0x7F,(char)0xBf,(char)0xFF
    };
    char enemyTypeList[4] = {
        ENEMY_SIMPLE_SLOW,
        ENEMY_SIMPLE_FAST,
        ENEMY_SMART_SLOW,
        ENEMY_SMART_FAST
    };

    bool isPointInvalid(char point);
    void drawMaze();
    void drawEnemy();
    void drawPlayer();
    void fillWithCandyAndWall();
    void drawPath();

public:
    MapGenerator(Map map, char difficulty);    
    void generateMap();
    
};