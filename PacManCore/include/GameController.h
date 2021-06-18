/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 21:30:28
 */
#pragma once
#include "utils.h"
#include "Player.h"
#include "Enemy.h"
#include "MapGenerator.h"

class GameController
{
private:
	Player* player;
	Enemy* enemyCollection[ENEMY_COUNT];
	MapGenerator* generator;
	Map map;
	void initialize();
	void dispose();

public:
	
	GameController(Map map):map(map){ initialize();}
	~GameController() { dispose(); };
	char tick(bool playerMoved, Key key);
	void restart();
	void restart(Map map);
	void updateMap(Map map);
};