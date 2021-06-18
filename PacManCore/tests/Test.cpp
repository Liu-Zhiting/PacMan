/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-18 18:13:42
 */
#pragma once
#include "utils.h"

#ifdef _DEBUG

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#endif


int32_t _stdcall UnitTest()
{
#ifdef _DEBUG
    
    int result = Catch::Session().run();
    return result;
#else
    return 0;
#endif
} 