/*
 * @Author: your name
 * @Date: 2021-05-11 20:35:00
 * @LastEditTime: 2021-06-15 19:33:21
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \PacMan\PacManCore\dllmain.cpp
 */
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

/// <summary>
///     应用程序的入口点
/// </summary>
/// <param name="hModule"></param>
/// <param name="ul_reason_for_call"></param>
/// <param name="lpReserved"></param>
/// <returns></returns>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

