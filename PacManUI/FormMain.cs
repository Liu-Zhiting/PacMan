using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PacManUI
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

enum Key {
    ARROW_UP,
    ARROW_LEFT,
    ARROW_DOWN,
    ARROW_RIGHT
};

    public partial class FormMain : Form
    {
        
        [DllImport("PacManCore.dll")]
        private static extern void InitGame(int a, int b, byte[] data);

        [DllImport("PacManCore.dll")]
        private static extern byte Tick(byte[] data,bool playerMoved, byte key);

        [DllImport("PacManCore.dll")]
        private static extern int GetPoint();

        [DllImport("PacManCore.dll")]
        private static extern void Restart(int a, int b, byte[] data);

        private static int a = 49;
        private static int b = 49;
        private static byte[] mapData = new byte[a*b];

        private static PictureBox[] picMap = new PictureBox[a * b];
        
        private readonly Image[] mapImage = {
            UIResource.EMPTY,
            UIResource.WALL,
            UIResource.CANDY,
            UIResource.CANDY_POWERED,
            UIResource.PLAYER,
            UIResource.PLAYER,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.CANDY_POWERED   //Debug
        };

        

        public FormMain()
        {
            InitializeComponent();
            MyInitialization();
        }


        private void MyInitialization()
        {
            //suspend layout
            SuspendLayout();

            //add picture box on the form
            int topInit = 62, leftInit = 62,step = 10;
            PictureBox picTmp; 
            for (int i = 0;i < a;i++)
            {
                for(int j = 0; j < b;j++)
                {
                    picTmp = new PictureBox
                    {
                        Top = topInit + i * step,
                        Left = leftInit + j * step,
                        Width = step,
                        Height = step,                        
                        SizeMode = PictureBoxSizeMode.StretchImage
                };
                    Controls.Add(picTmp);
                    picMap[i * b + j] = picTmp;
                }
            }

            //resume layout
            ResumeLayout(false);
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < a; i++)
                for (int j = 0; j < b; j++)
                    mapData[i * b + j] = 0;
            InitGame(a,b,mapData);
            LoadMap();
        }

        private void LoadMap()
        {           
            for(int i = 0;i < a;i++)
            {
                for(int j = 0; j < b; j++)
                {
                    picMap[i * b + j].Image = mapImage[mapData[i * b + j]];
                }
            }
        }

        private void ticker_Tick(object sender, EventArgs e)
        {
            Tick(mapData,false,0);
            LoadMap();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ticker.Start();
        }

       
    }
}
