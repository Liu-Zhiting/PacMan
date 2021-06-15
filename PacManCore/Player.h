#pragma once
#include "utils.h"
#include "Movable.h"

class Player: public Movable
{
private:
    int poweredTime;
    int point;

public:
    Player(int position,Map map);
    void moveAndEat(Key key);
    int getPoint() const { return point;}
    bool isPowered() const { return (poweredTime > 0);}
    void minusPoweredTime();
};