// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"


//将给定的数组初始化为高为a、宽为b的地图
//参数：
//int a: 地图的高
//int b: 地图的宽
//int* data: 长度为a*b的地图，按行排列
void _stdcall GetNewMap(const int a, const int b, int data[]);

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

