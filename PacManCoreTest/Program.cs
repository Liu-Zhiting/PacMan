using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace PacManCoreTest
{
    class Program
    {
        [DllImport("PacManCore.dll")]
        private static extern int UnitTest();

        static void Main(string[] args)
        {
            int result = UnitTest();
        }
    }
}
