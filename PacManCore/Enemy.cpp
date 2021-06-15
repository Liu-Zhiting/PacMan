#include "pch.h"
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
    this->groundBlock = CANDY;
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
    int nextPosition = (this->isSmart) ? getTargetedStep(target): getRandomStep();
    if(position == nextPosition)
        return;
    updateMap(nextPosition);
    this->position = nextPosition;
}

void Enemy::updateMap(int nextPosition)
{
    if(PLAYER == map.data[nextPosition] || PLAYER_POWERED == map.data[nextPosition])
    {
        map.data[nextPosition] = PLAYER_WITH_ENEMY;
    }
    else
    {
        map.data[nextPosition] = this->type;
    }
    map.data[position] = groundBlock;
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
        {
            found = true;
            break;
        }
                
        for (int i = 0; i < 4; i++)
        {
            int index = q.front() + next[i];
            if(map.isPointInvalid(index))
                {continue;}
            if (visited[index])
                {continue;}
            if (inBlockList(map.data[index]))
            {
                visited.at(index) = true;
                continue;
            }
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