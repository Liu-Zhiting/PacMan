#pragma once
#include "utils.h"

class Movable
{
protected:
    int position;
    Map map;
    int next[4];
    bool dead;

public:
    Movable(int position,Map map):map(map)
    {
        this->position = position;
        this->map = map;
        this->next[ARROW_UP] = -map.b;
	    this->next[ARROW_LEFT] = -1;
	    this->next[ARROW_DOWN] = map.b;
	    this->next[ARROW_RIGHT] = 1;
        this->dead = false;
    }

    int getPosition() const { return position; }
    bool isDead() const { return dead; }
    void kill() { dead = true; }

};

