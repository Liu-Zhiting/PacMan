/*
 * @Author: SMagic
 * @Date: 2021-06-16 00:22:49
 * @LastEditors: SMagic
 * @LastEditTime: 2021-06-24 16:50:13
 */

#include "utils.h"

Map::Map(int a, int b, char* data)
{
    this->a = a;
    this->b = b;
    this->data = data;
    this->left_up = b + 1;
    this->right_up = b + b - 2;
    this->left_down = (a - 2) * b + 1;
    this->right_down = (a - 2) * b + b - 2;
}

bool Map::isPointInvalid(int point)
{
    return (point < left_up || point > right_down || 
        0 == point % b || b - 1 == point % b);
}

#ifdef _DEBUG
void Map::printData()
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            cout << data[i * b + j] << " ";
        }
        cout << endl;
    }
}

void Map::printItem() //■○●△▲
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            switch (data[i * b + j])
            {
            case WALL:
                cout << "■";
                break;
            case ENEMY_SMART_SLOW:
            case ENEMY_SMART_FAST:
            case ENEMY_SIMPLE_SLOW:
            case ENEMY_SIMPLE_FAST:
                cout << "△"; 
                break;
            case PLAYER_POWERED:
            case PLAYER:
                cout << "▲";
                break;
            case CANDY:
                cout << "○";
                break;
            case CANDY_POWERED:
                cout << "●";
                break;
            default:
                cout << "  ";
                break;
            }                
        }
        cout << endl;
    }
}
#endif // DEBUG
