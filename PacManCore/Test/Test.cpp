/*
 * @Author: your name
 * @Date: 2021-06-13 20:47:00
 * @LastEditTime: 2021-06-15 19:54:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\Test\Test.cpp
 */
#include "pch.h"

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