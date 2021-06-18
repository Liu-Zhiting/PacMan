/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 18:09:58
 */
#include "utils.h"
#include "Disjointset.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator(Map map):map(map)
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

    //init random seed
    srand((unsigned)time(NULL));
}

void MapGenerator::drawMaze()
{
    //init
    DisjointSet set(map.a * map.b);
    int neighbor[4] = { -2,-2 * map.b, 2,2 * map.b };
    int tmpPointA, tmpPointB, tmpI, tmpJ;

    //use disjoint set to generate maze
    while (set.find(map.left_up) != set.find(map.right_down) ||
            set.find(map.left_down) != set.find(map.right_up))
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
    drawEnemy();
    drawPlayer();
}

void MapGenerator::drawEnemy()
{
    int center = (map.a * map.b) >> 1;
    int next[4] = {-2-2*map.b,2-2*map.b,-2+2*map.b,2+2*map.b};
    for(int i = 0;i < 5; i++)
        for(int j = 0;j < 5; j++)
            map.data[center + next[0] + i*map.b + j] = (char)CANDY;
    map.data[center + next[0]] = (char)ENEMY_SIMPLE_FAST;
    map.data[center + next[1]] = (char)ENEMY_SIMPLE_SLOW;
    map.data[center + next[2]] = (char)ENEMY_SMART_FAST;
    map.data[center + next[3]] = (char)ENEMY_SMART_SLOW;
}

void MapGenerator::drawPlayer()
{
    int index = (map.left_down + map.right_down) >> 1;
    map.data[index] = (char)PLAYER;
    map.data[index - 1] = (char)CANDY;
    map.data[index + 1] = (char)CANDY;
    map.data[index - map.b] = (char)CANDY;
}

