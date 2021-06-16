#include "utils.h"
#include "Disjointset.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator(Map map):map(map)
{
    this->a = map.a;
    this->b = map.b;
    this->data = map.data;

    //check if a,b positive odd integers
    if (0 == (a & 1))
        a--;
    if (0 == (b & 1))
        b--;
    if (a <= 0 || b <= 0) {
        throw "Argument exception: argument a,b of MapGenerator must be positive";
        return;
    }

    //init random seed
    srand((unsigned)time(NULL));

    //init local variable
    this->left_up = b + 1;
    this->right_up = b + b - 2;
    this->left_down = (a - 2) * b + 1;
    this->right_down = (a - 2) * b + b - 2;
}

bool MapGenerator::isPointInvalid(int point)
{
    return (point < left_up || point > right_down || 
        0 == point % b || b - 1 == point % b);
}

void MapGenerator::drawMaze()
{
    //init
    DisjointSet set(a * b);
    int neighbor[4] = { -2,-2 * b, 2,2 * b };
    int tmpPointA, tmpPointB, tmpI, tmpJ;

    //use disjoint set to generate maze
    while (set.find(left_up) != set.find(right_down) ||
            set.find(left_down) != set.find(right_up))
    {
        //get new tmpPoint
        tmpI = rand() % a;
        tmpI |= 1;   //change tmpI into odd integer
        tmpJ = rand() % b;
        tmpJ |= 1;
        tmpPointA = tmpI * b + tmpJ;
        tmpPointB = tmpPointA + neighbor[rand() % 4];

        //check if tmpPoint out of range
        if (isPointInvalid(tmpPointA) || isPointInvalid(tmpPointB))
            continue;

        //if wall exists, destroy wall
        if (set.find(tmpPointA) != set.find(tmpPointB))
        {
            set.unionSet(tmpPointA, tmpPointB);
            data[(tmpPointA + tmpPointB) >> 1] = CANDY;
        }

    }

    
}

void MapGenerator::fillWithCandyAndWall()
{
    //fill map with wall
    for (int i = 0; i < a * b; i++)
        data[i] = WALL;

    //put candy
    for (int i = 1; i <= a - 2; i += 2)
        for (int j = 1; j <= b - 2; j += 2)
            data[i * b + j] = CANDY;

    //put powered candy
    data[b + 1] = CANDY_POWERED;
    data[b + b - 2] = CANDY_POWERED;
    data[(a - 2) * b + 1] = CANDY_POWERED;
    data[(a - 2) * b + b - 2] = CANDY_POWERED;
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
    int center = (a * b) >> 1;
    int next[4] = {-2-2*b,2-2*b,-2+2*b,2+2*b};
    data[center + next[0]] = ENEMY_SIMPLE_FAST;
    data[center + next[1]] = ENEMY_SIMPLE_SLOW;
    data[center + next[2]] = ENEMY_SMART_FAST;
    data[center + next[3]] = ENEMY_SMART_SLOW;
}

void MapGenerator::drawPlayer()
{
    int range[4] = {left_up,left_down,right_up,right_down};
    data[range[rand() % 4]] = PLAYER;
}

