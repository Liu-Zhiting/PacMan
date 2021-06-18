/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-17 00:37:33
 */
#pragma once
#include "utils.h"
#include "../catch.hpp"
#include "Player.h"

TEST_CASE("Player.h")
{
    int a = 9;
    int b = 9;
    char * data = new char[a * b * sizeof(char)];
    memset(data, 0, a * b * sizeof(char));
    Map map(a,b,data);
    const int next[4] = {-1, - map.b,1,map.b};

    int pos = 40;
    Player player(pos,map);

    SECTION("player initialization")
    {
        REQUIRE(0 == player.getPoint());
    }

    SECTION("player can move")
    {
        player.moveAndEat(ARROW_DOWN);
        REQUIRE(49 == player.getPosition());
        REQUIRE(PLAYER == map.data[49]);
        player.moveAndEat(ARROW_UP);
        player.moveAndEat(ARROW_UP);
        REQUIRE(31 == player.getPosition());
        REQUIRE(PLAYER == map.data[31]);
        player.moveAndEat(ARROW_LEFT);
        REQUIRE(30 == player.getPosition());
        REQUIRE(PLAYER == map.data[30]);
        player.moveAndEat(ARROW_RIGHT);
        REQUIRE(31 == player.getPosition());
        REQUIRE(PLAYER == map.data[31]);
    }

    SECTION("player can eat and can be stronger")
    {
        map.data[pos - 1] = CANDY;
        player.moveAndEat(ARROW_LEFT);
        REQUIRE(1 == player.getPoint());
        
        map.data[pos - 2] = CANDY_POWERED;
        player.moveAndEat(ARROW_LEFT);
        REQUIRE(2 == player.getPoint());
        REQUIRE(player.isPowered());
        REQUIRE(PLAYER_POWERED == map.data[player.getPosition()]);
    }

    SECTION("player meet with enemy")
    {
        map.data[pos - 1] = ENEMY_SIMPLE_SLOW;
        player.moveAndEat(ARROW_LEFT);
        REQUIRE(PLAYER_WITH_ENEMY == map.data[pos - 1]);
    }

    SECTION("player could be blocked")
    {
        map.data[pos - 1] = WALL;
        player.moveAndEat(ARROW_LEFT);
        REQUIRE(pos == player.getPosition());
    }


}