/*
 * @Author: your name
 * @Date: 2021-06-13 20:47:00
 * @LastEditTime: 2021-06-24 17:03:26
 * @LastEditors: SMagic
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\Test\EnemyTest.cpp
 */
#pragma once
#include "utils.h"
#include "../catch.hpp"
#include "Enemy.h"

TEST_CASE("Enemy.h")
{
    int a = 9;
    int b = 9;
    char * data = new char[a * b * sizeof(char)];
    memset(data, 0, a * b * sizeof(char));
    Map map(a,b,data);
    const int next[4] = {-1, - map.b,1,map.b};


    
    int pos = 40;
    map.data[pos] = ENEMY_SIMPLE_SLOW;
    Enemy enemy1(ENEMY_SIMPLE_SLOW,pos,map);
    enemy1.clearSlowTime();
    Enemy enemy2(ENEMY_SMART_SLOW,pos,map);
    enemy2.clearSlowTime();

    SECTION("initialize")
    {
        REQUIRE(enemy1.getPosition() == pos);
        REQUIRE(ENEMY_SIMPLE_SLOW == enemy1.getType());
    }

    SECTION("enemy could random move")
    {
        enemy1.move(0);
        bool flag = false;
        for(int i = 0; i < 4; i++)
            flag = flag || ((pos + next[i]) == enemy1.getPosition());
        REQUIRE(flag);
    }

    SECTION("enemy could be blocked")
    {
        for(int i = 0; i < 4; i++)
            map.data[pos + next[i]] = WALL;
        CHECK(WALL == map.data[31]);
        enemy1.move(0);
        REQUIRE(pos == enemy1.getPosition());
    }

    SECTION("enemy could move to target")
    {
        map.data[pos] = ENEMY_SMART_SLOW;
        enemy2.move(38);
        REQUIRE(39 == enemy2.getPosition());
    }

    SECTION("enemy could targeted move and avoid barrier")
    {
        map.data[pos] = ENEMY_SMART_SLOW;
        map.data[pos - 1] = WALL;
        enemy2.move(pos - 2);
        bool flag = (enemy2.getPosition() == pos - map.b) || (enemy2.getPosition() == pos + map.b);
        CHECK(flag);
        CHECK(WALL == map.data[pos - 1]);
    }

    SECTION("enemy with player")
    {
        map.data[pos - 1] = PLAYER;
        enemy2.move(pos-2);
        REQUIRE(PLAYER_WITH_ENEMY ==  map.data[pos - 1]);
    }

}

