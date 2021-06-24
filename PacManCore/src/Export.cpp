/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 22:15:52
 */

#include "utils.h"
#include "GameController.h"

/// <summary>
/// 
/// </summary>
GameController* pController = nullptr;

/// <summary>
/// 
/// </summary>
Map* pMap = nullptr;


uint32_t globalPoint = 0;

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="data"></param>
/// <returns></returns>
void _stdcall InitGame(const uint32_t a, const uint32_t b, char data[],char difficulty)
{
    srand((unsigned)time(NULL));
    pMap = new Map(a,b,data);
    pController = new GameController(*pMap,difficulty);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
char _stdcall Tick(char* mapData, bool playerMoved, char key)
{
    pMap->data = mapData;
    if(nullptr != pController)
    {
        pController->updateMap(*pMap);
        return pController->tick(playerMoved,(Key)key);
    }
    else { return 1; }
}

uint32_t _stdcall GetPoint()
{
    return globalPoint;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
void _stdcall Restart(const uint32_t a, const uint32_t b, char* mapData,char difficulty)
{
    delete pMap;
    pMap = new Map(a,b,mapData);
    if(nullptr != pController)
    {
        pController->restart(*pMap,difficulty);
    }
}
