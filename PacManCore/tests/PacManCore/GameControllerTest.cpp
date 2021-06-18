/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 17:50:52
 */
#pragma once
#include "utils.h"
#include "GameController.h"
#include "../catch.hpp"
#include "framework.h"

TEST_CASE("GameController.h")
{
    int a = 27;
    int b = 27;
    char * data = new char[a * b * sizeof(char)];
    memset(data, 0, a * b * sizeof(char));
    Map map(a,b,data);
    const int next[4] = {-1, - map.b,1,map.b};

    GameController controller(map);
      
    SECTION("controller initialiaztion")
    {
        cout << "========Initialization Succeeded========" << endl;
        map.printItem();
        Sleep(1000);
        system("cls");
    }

    SECTION("controller could tick")
    {
        for (int i = 0; i < 30; i++)
        {
            system("cls");
            cout << "========Tick " << (i+1) << " ========" << endl;
            controller.tick(false,ARROW_DOWN);
            map.printItem();
            Sleep(300);
        }
    }

}