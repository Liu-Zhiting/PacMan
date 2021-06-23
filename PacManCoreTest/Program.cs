using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;

namespace PacManCoreTest
{
    enum EntityType {
    EMPTY,
    WALL,
    CANDY,
    CANDY_POWERED,
    PLAYER,
    PLAYER_POWERED,
    ENEMY_SIMPLE_FAST,
    ENEMY_SIMPLE_SLOW,
    ENEMY_SMART_FAST,
    ENEMY_SMART_SLOW,
    PLAYER_WITH_ENEMY
};

    class Program
    {
        [DllImport("PacManCore.dll")]
        private static extern int UnitTest();

        [DllImport("PacManCore.dll")]
        private static extern void InitGame(int a, int b, byte[] data);

        [DllImport("PacManCore.dll")]
        private static extern byte Tick(byte[] data,bool playerMoved, byte key);

        [DllImport("PacManCore.dll")]
        private static extern int GetPoint();

        [DllImport("PacManCore.dll")]
        private static extern void Restart(int a, int b, byte[] data);
        public static void Pause()
        {
            Console.Write("Press any key to continue . . .");
            Console.ReadKey(true);
        }
        static void printItem(int a, int b, byte[] data)
        {
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    switch ((EntityType)data[i * b + j])
                    {
                    case EntityType.WALL:
                        Console.Write("■");
                        break;
                    case EntityType.ENEMY_SMART_SLOW:
                    case EntityType.ENEMY_SMART_FAST:
                    case EntityType.ENEMY_SIMPLE_SLOW:
                    case EntityType.ENEMY_SIMPLE_FAST:
                        Console.Write("△");
                        break;
                    case EntityType.PLAYER_POWERED:
                    case EntityType.PLAYER:
                        Console.Write("▲");
                        break;
                    default:
                        Console.Write("  ");
                        break;
                    }                
                }
                Console.WriteLine();
            }
        }
        static int a = 49, b = 49;
        static byte[] data = new byte [a*b];

        static void Main(string[] args)
        {
            //unit test
            // int result = UnitTest();

            // try init game
            Pause();
            InitGame(a,b,data);
            printItem(a,b,data);
            Pause();

            for(int i = 0; i < 50;i++)
            {
                Console.Clear();
                Tick(data,true,(byte)(i % 4));
                printItem(a,b,data);
                // Pause();
                Thread.Sleep(200);
            }

            

        }

    }
}
