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
	int tick(bool playerMoved, Key key);
	void restart();
	void restart(Map map);
};