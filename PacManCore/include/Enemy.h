/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 17:02:20
 */
#pragma once
#include "utils.h"
#include "Movable.h"



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
    int slowTime;
	EntityType groundBlock;

    int getRandomStep();
    int getTargetedStep(int target);
    void writeMap(int nextPosition);
    
    bool isBlocked();

public:
    Enemy(EntityType type, int position, Map map);
    void move(const int target);
    EntityType getType() const { return type; }
    void tryRestart();

#ifdef _DEBUG
    void clearSlowTime(){slowTime = 0;}
#endif
};