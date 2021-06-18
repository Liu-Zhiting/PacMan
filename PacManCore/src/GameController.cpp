/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 21:32:16
 */

#include "utils.h"
#include "GameController.h"

extern uint32_t globalPoint;

void GameController::initialize()
{
    generator = new MapGenerator(map);
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
            enemyCollection[i]->kill();
            map.data[player->getPosition()] = PLAYER_POWERED;
        }
        else
        {
            player->kill();
            map.data[player->getPosition()] = enemyCollection[i]->getType();
        }
    }    

    // copy point to globalPoint
    globalPoint = player->getPoint();

    // buff time count down
    player->minusPoweredTime();

    return 0;
}

void GameController::restart()
{
    dispose();
    initialize();
}

void GameController::restart(Map map)
{
    dispose();
    this->map = map;
    initialize();
}

void GameController::updateMap(Map map)
{
    this->map = map;
    this->player->updateMap(map);
    for(int i = 0; i < ENEMY_COUNT;i++)
        enemyCollection[i]->updateMap(map);
}