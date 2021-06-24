/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 22:12:56
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
	void initialize(char difficulty);
	void dispose();

public:
	
	GameController(Map map, char difficulty):map(map){ initialize(difficulty);}
	~GameController() { dispose(); };
	char tick(bool playerMoved, Key key);
	void restart(Map map,char difficulty);
	void updateMap(Map map);
};