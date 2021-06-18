/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-17 11:00:40
 */
#pragma once
#include "utils.h"
#include "Movable.h"

class Player: public Movable
{
private:
    int poweredTime;
    uint32_t point;

public:
    Player(int position,Map map);
    void moveAndEat(Key key);
    uint32_t getPoint() const { return point;}
    bool isPowered() const { return (poweredTime > 0);}
    void minusPoweredTime();
};