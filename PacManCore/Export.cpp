/*
 * @Author: your name
 * @Date: 2021-06-15 19:30:35
 * @LastEditTime: 2021-06-15 19:55:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\Export.cpp
 */
#include "pch.h"
#include "GameController.h"

/// <summary>
/// 
/// </summary>
GameController* pController = nullptr;

/// <summary>
/// 
/// </summary>
Map* pMap = nullptr;


int globalPoint = 0;

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="data"></param>
/// <returns></returns>
void _stdcall InitGame(const int a, const int b, int data[])
{
    pMap = new Map(a,b,data);
    pController = new GameController(*pMap);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int _stdcall Tick(bool playerMoved, int key)
{
    if(nullptr != pController)
    {
        return pController->tick(playerMoved,(Key)key);
    }
    else { return -1; }
}

int _stdcall GetPoint()
{
    return globalPoint;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
void _stdcall Restart()
{
    if(nullptr != pController)
    {
        pController->restart();
    }
}
