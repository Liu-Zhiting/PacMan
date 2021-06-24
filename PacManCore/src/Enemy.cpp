/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 01:59:00
 */

#include "utils.h"
#include "Enemy.h"
#include <queue>
#include <vector>
using std::queue;
using std::vector;

Enemy::Enemy(EntityType type, int position,Map map):Movable(position,map)
{
    this->type = type;
    this->isSmart = ENEMY_SMART_FAST == type || ENEMY_SMART_SLOW == type;
    this->isFast = ENEMY_SIMPLE_FAST == type || ENEMY_SMART_FAST == type;
    this->dead = false;
    this->restartTime = ENEMY_RESTART_TIME;
    this->slowTime = ENEMY_SLOW_TIME;
    this->groundBlock = CANDY;
}

void Enemy::tryRestart()
{
    if(!dead)
        return;
    if(restartTime-- > 0)
        return;

    //reset state
    restartTime = ENEMY_RESTART_TIME;
    this->dead = false;

    //give enemy random position
    int tail = 0;
    int randList[25] = {0};
    int center = (map.a * map.b) >> 1;
    int next[4] = {-2-2*map.b,2-2*map.b,-2+2*map.b,2+2*map.b};
    for(int i = 0;i < 5; i++)
        for(int j = 0;j < 5; j++)
            if(EMPTY == map.data[center + next[0] + i*map.b + j] 
                || CANDY == map.data[center + next[0] + i*map.b + j])
                randList[tail++] = center + next[0] + i*map.b + j;
    int pos = randList[rand() % tail];
    position = pos;
    map.data[pos] = (char)this->type;

    //reset powered candy
    map.data[map.left_up] = CANDY_POWERED;
    map.data[map.left_down] = CANDY_POWERED;
    map.data[map.right_up] = CANDY_POWERED;
    map.data[map.right_down] = CANDY_POWERED;
    
}

bool Enemy::isBlocked()
{
    bool result = true;
    int tmp,index;
    for (int i = 0; i < 4; i++)
    {
        index = position + next[i];
        tmp = map.data[index];
        result = result && inBlockList(tmp);
    }
        
    return result;
}

bool Enemy::inBlockList(int type)
{
    for (int i = 0; i < LEN_BLOCK_LIST; i++)
        if (type == blockList[i])
            return true;
    return false;
}

void Enemy::move(const int target)
{
    if (isBlocked() || dead)
        return;
    if(!isFast)
    {
        if(slowTime-- > 0)
            return;
        slowTime = ENEMY_SLOW_TIME;
    }
    
    int nextPosition = (this->isSmart) ? getTargetedStep(target): getRandomStep();
    if(position == nextPosition)
        return;
    writeMap(nextPosition);
    this->position = nextPosition;
}

void Enemy::writeMap(int nextPosition)
{
    map.data[position] = (char)groundBlock;
    if(PLAYER == map.data[nextPosition] || PLAYER_POWERED == map.data[nextPosition])
    {
        groundBlock = EMPTY;
        map.data[nextPosition] = (char)PLAYER_WITH_ENEMY;
    }
    else
    {
        groundBlock = (EntityType)map.data[nextPosition];
        map.data[nextPosition] = (char)(this->type);
    }
}

int Enemy::getRandomStep()
{
    int nextPosition = position + next[rand() % 4];
    while (inBlockList(map.data[nextPosition]))
        nextPosition = position + next[rand() % 4];  //TODO optimize
    return nextPosition;
}

int Enemy::getTargetedStep(const int target)
{
    if(target == position)
        return position;

    //init variables
    bool found = false;
    int nextPosition;
    queue<int> q;
    vector<bool> visited(map.a * map.b);
    vector<int> previous(map.a * map.b);
    for(int i = 0;i < map.a * map.b;i++)
    {
        visited[i] = (map.data[i] == WALL);
        previous[i] = -1;
    }
    
    //init first 4 positions
    visited.at(position) = true;
    for (int i = 0; i < 4; i++)
    {
        int index = position + next[i];
        visited.at(index) = true;
        if (inBlockList(map.data[index]))
            continue;
        q.push(position + next[i]);
    }        

    //bfs
    while (!q.empty())
    {
        if (target == q.front())
            {found = true; break;}
                
        for (int i = 0; i < 4; i++)
        {
            int index = q.front() + next[i];
            if(map.isPointInvalid(index))
                {continue;}
            if (visited[index])
                {continue;}
            if (WALL == (map.data[index]))
                {visited.at(index) = true; continue;}
            q.push(index);
            visited.at(index) = true;
            previous.at(index) = q.front();
        }
        q.pop();
    }

    //trace back to find out nextPosition
    if(found)
    {
        nextPosition = target;
        while (previous[nextPosition] != -1)
            nextPosition = previous[nextPosition];
    }
    else
    {
        nextPosition = getRandomStep();
    }
    return nextPosition;
}