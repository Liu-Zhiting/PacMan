/*
 * @Author: your name
 * @Date: 2021-06-13 20:47:00
 * @LastEditTime: 2021-06-16 00:55:53
 * @LastEditors: SMagic
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\Test\Test.cpp
 */
#pragma once
#include "utils.h"

#ifdef _DEBUG

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#endif


int _stdcall UnitTest()
{
#ifdef _DEBUG
    int result = Catch::Session().run();
    system("pause");
    return result;
#else
    return 0;
#endif
} 