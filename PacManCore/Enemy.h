#pragma once
#include "utils.h"
#include "Movable.h"
#define LEN_BLOCK_LIST 6

class Enemy : public Movable
{
private:
    constexpr static EntityType blockList[LEN_BLOCK_LIST] = {
    WALL,
    ENEMY_SIMPLE_FAST,
    ENEMY_SIMPLE_SLOW,
    ENEMY_SMART_FAST,
    ENEMY_SMART_SLOW,
    PLAYER_WITH_ENEMY
    };
    bool static inBlockList(int type);

    EntityType type;
    bool isSmart;
    bool isFast;
    int restartTime;
	EntityType groundBlock;

    int getRandomStep();
    int getTargetedStep(int target);
    void updateMap(int nextPosition);
    
    bool isBlocked();

public:
    Enemy(EntityType type, int position, Map map);
    void move(const int target);
    EntityType getType() const { return type; }
};