/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 23:51:42
 */

#include "utils.h"
#include "GameController.h"

extern uint32_t globalPoint;

void GameController::initialize(char difficulty)
{
    generator = new MapGenerator(map,difficulty);
    generator->generateMap();
    int enemy_tail = 0;
    for(int i = 0; i < map.a*map.b;i++)
    {
        switch(map.data[i])
        {
            case PLAYER:
            case PLAYER_POWERED:
                player = new Player(i,map);
                break;
            case ENEMY_SIMPLE_FAST:
            case ENEMY_SIMPLE_SLOW:
            case ENEMY_SMART_FAST:
            case ENEMY_SMART_SLOW:
                enemyCollection[enemy_tail++] = 
                    new Enemy((EntityType)(map.data[i]),i,map);
                break;
        }
    }
}

void GameController::dispose()
{
    delete generator;
    delete player;
    for(int i = 0; i < ENEMY_COUNT;i++)
        delete enemyCollection[i];
}

char GameController::tick(bool playerMoved, Key key)
{
    // end game if player dead
    if(player->isDead())
        return 1;

    // get player and enemies move
    if(playerMoved)
        player->moveAndEat(key);
    for(int i = 0;i < ENEMY_COUNT;i++)
        enemyCollection[i]->move(player->getPosition());

    // decide to kill player or enemy when meeting
    for(int i = 0; i < ENEMY_COUNT;i++)
    {
        if(enemyCollection[i]->getPosition() != player->getPosition())
            continue;
        if(player->isPowered())
        {
            map.data[player->getPosition()] = PLAYER_POWERED;
            enemyCollection[i]->kill();
            break;
        }
        else
        {
            map.data[player->getPosition()] = enemyCollection[i]->getType();
            player->kill();
            break;
        }
    }    

    // copy point to globalPoint
    globalPoint = player->getPoint();

    // buff time count down
    player->minusPoweredTime();

    //try to restart dead enemy
    for(int i = 0;i < ENEMY_COUNT;i++)
        enemyCollection[i]->tryRestart();

    return 0;
}

void GameController::restart(Map map,char difficulty)
{
    dispose();
    this->map = map;
    initialize(difficulty);
}

void GameController::updateMap(Map map)
{
    this->map = map;
    this->player->updateMap(map);
    for(int i = 0; i < ENEMY_COUNT;i++)
        enemyCollection[i]->updateMap(map);
}