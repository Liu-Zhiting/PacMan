/*
 * @Author: your name
 * @Date: 2021-06-07 10:38:40
 * @LastEditTime: 2021-06-15 19:51:15
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\GameController.cpp
 */
#include "pch.h"
#include "GameController.h"

extern int globalPoint;

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

int GameController::tick(bool playerMoved, Key key)
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