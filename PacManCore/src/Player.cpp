﻿/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 21:33:03
 */

#include "utils.h"
#include "player.h"

Player::Player(int position,Map map):Movable(position,map)
{
    this->poweredTime = 0;
    this->dead = false;
    this->point = 0;
}

void Player::moveAndEat(Key key)
{
    bool metEnemy = false;
    int nextPosition = position + next[key];
    if (dead) 
        return;
    switch(map.data[position + next[key]])
    {
        case WALL:
            return;
        case ENEMY_SIMPLE_FAST:
        case ENEMY_SIMPLE_SLOW:
        case ENEMY_SMART_FAST:
        case ENEMY_SMART_SLOW:
            if(poweredTime > 0)
                this->dead = true;
            metEnemy = true;
            break;
        case CANDY:
            point += 1;
            break;
        case CANDY_POWERED:
            poweredTime = POWERED_BUFF_TIME;
            point += 1;
            break;
    }

    map.data[position] = EMPTY;
    if(metEnemy)
        map.data[position + next[key]] = (char)PLAYER_WITH_ENEMY;
    else
        map.data[position + next[key]] = (poweredTime > 0) ? (char)PLAYER_POWERED : (char)PLAYER;
    position = nextPosition;
}

void Player::minusPoweredTime()
{
    if(poweredTime > 0)
        poweredTime -= 1;
}