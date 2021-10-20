/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 23:58:50
 */
#include "utils.h"
#include "Disjointset.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator(Map map, char difficulty):map(map)
{
    //check if a,b positive odd integers
    if (0 == (map.a & 1))
        map.a--;
    if (0 == (map.b & 1))
        map.b--;
    if (map.a <= 0 || map.b <= 0) {
        throw "Argument exception: argument a,b of MapGenerator must be positive";
        return;
    }
    this->difficulty = difficulty;
}

void MapGenerator::drawMaze()
{
    //init
    DisjointSet set(map.a * map.b);
    int neighbor[4] = { -2,-2 * map.b, 2,2 * map.b };
    int tmpPointA, tmpPointB, tmpI, tmpJ;

    //use disjoint set to generate maze
    while (set.find(map.left_up) != set.find(map.right_down) 
            || set.find(map.left_down) != set.find(map.right_up) )
    {
        //get new tmpPoint
        tmpI = rand() % map.a;
        tmpI |= 1;   //change tmpI into odd integer
        tmpJ = rand() % map.b;
        tmpJ |= 1;
        tmpPointA = tmpI * map.b + tmpJ;
        tmpPointB = tmpPointA + neighbor[rand() % 4];

        //check if tmpPoint out of range
        if (map.isPointInvalid((tmpPointA + tmpPointB) >> 1))
            continue;

        //if wall exists, destroy wall
        if (set.find(tmpPointA) != set.find(tmpPointB))
        {
            set.unionSet(tmpPointA, tmpPointB);
            map.data[(tmpPointA + tmpPointB) >> 1] = (char)CANDY;
        }
    }    
}

void MapGenerator::fillWithCandyAndWall()
{
    //fill map with wall
    for (int i = 0; i < map.a * map.b; i++)
        map.data[i] = (char)WALL;

    //put candy
    for (int i = 1; i <= map.a - 2; i += 2)
        for (int j = 1; j <= map.b - 2; j += 2)
            map.data[i * map.b + j] = (char)CANDY;

    //put powered candy
    map.data[map.b + 1] = (char)CANDY_POWERED;
    map.data[map.b + map.b - 2] = (char)CANDY_POWERED;
    map.data[(map.a - 2) * map.b + 1] = (char)CANDY_POWERED;
    map.data[(map.a - 2) * map.b + map.b - 2] = (char)CANDY_POWERED;
}

void MapGenerator::generateMap()
{
    fillWithCandyAndWall();
    drawMaze();
    drawPath();
    drawEnemy();
    drawPlayer();
}

void MapGenerator::drawEnemy()
{
    int center = (map.a * map.b) >> 1;
    int next[4] = {-2-2*map.b,2-2*map.b,-2+2*map.b,2+2*map.b};

    //parse enemy type
    char enemyTypeCode = typeBitmap[difficulty];
    for(int i = 0; i < 4;i++)
    {
        map.data[center + next[i]] = enemyTypeList[(enemyTypeCode & 0x03)];
        enemyTypeCode >>= 2;
    }
}

void MapGenerator::drawPlayer()
{
    int index = (map.left_down + map.right_down) >> 1;
    map.data[index] = (char)PLAYER;
    map.data[index - 1] = (char)CANDY;
    map.data[index + 1] = (char)CANDY;
    map.data[index - map.b] = (char)CANDY;
    map.data[index - map.b - 1] = (char)CANDY;
    map.data[index - map.b + 1] = (char)CANDY;
}

void MapGenerator::drawPath()
{
    //draw center square
    int center = (map.a * map.b) >> 1;
    int next[4] = {-2-2*map.b,2-2*map.b,-2+2*map.b,2+2*map.b};
    for(int i = 0;i < 5; i++)
        for(int j = 0;j < 5; j++)
            map.data[center + next[0] + i*map.b + j] = (char)CANDY;

    //draw path around            
    for(int i = 1; i < map.right_up - map.left_up; i++)
    {
        map.data[map.left_up + i] = CANDY;
        map.data[map.left_down + i] = CANDY;
    }
    for(int j = map.b; j < map.left_down - map.left_up; j+=map.b)
    {
        map.data[map.left_up + j] = CANDY;
        map.data[map.right_up + j] = CANDY;
    }
    map.data[map.left_up + map.b + 1] = CANDY;
    map.data[map.left_down - map.b + 1] = CANDY;
    map.data[map.right_up + map.b - 1] = CANDY;
    map.data[map.right_down - map.b - 1] = CANDY;
}

