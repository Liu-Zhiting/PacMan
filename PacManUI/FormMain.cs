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
    enum EntityType
    {
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

    enum Key
    {
        ARROW_UP,
        ARROW_LEFT,
        ARROW_DOWN,
        ARROW_RIGHT
    };

    public partial class FormMain : Form
    {
        [DllImport("PacManCore.dll")]
        private static extern void InitGame(int a, int b, byte[] data,byte difficulty);

        [DllImport("PacManCore.dll")]
        private static extern byte Tick(byte[] data,bool playerMoved, byte key);

        [DllImport("PacManCore.dll")]
        private static extern int GetPoint();

        [DllImport("PacManCore.dll")]
        private static extern void Restart(int a, int b, byte[] data,byte difficulty);

        private static int a = 27;
        private static int b = 33;
        private static int pointThreshold =  (int)(a*b*0.40 * 0.5);
        private static int level = 0;
        private const int MAX_LEVEL = 34;
        private static byte[] mapData = new byte[a * b];
        private static byte[] compareData = new byte[a * b];

        private bool playerMoved = false;

        private Key key;
        private static PictureBox[] picMap = new PictureBox[a * b];

        private readonly Image[] mapImage = {
            UIResource.EMPTY,
            UIResource.WALL,
            UIResource.CANDY,
            UIResource.CANDY_POWERED,
            UIResource.PLAYER,
            UIResource.PLAYER_POWERED,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.ENEMY,
            UIResource.CANDY_POWERED   //Debug
        };

        public FormMain()
        {
            InitializeComponent();
            FormMapInitialzation();
        }

        private void FormMapInitialzation()
        {
            //suspend layout
            SuspendLayout();
            Height = Screen.PrimaryScreen.Bounds.Height;
            Width = Screen.PrimaryScreen.Bounds.Width;

            //add picture box on the form
            int topInit = 0, leftInit = 0, step = this.Height / a;

            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    PictureBox picTmp;
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
            InitGame(a, b, mapData,0);
            mapData.CopyTo(compareData, 0);
            for (int index = 0; index < a * b; index++)
                picMap[index].Image = mapImage[mapData[index]];

            //set label
            labelLevel.Text = "关卡：" + (level+1);
            labelPointThreshold.Text = "目标分数：" + pointThreshold;
        }

        private void updateMap()
        {
            Parallel.For(0, a * b, index =>
                {
                    if (mapData[index] != compareData[index])
                    {
                        picMap[index].Image = mapImage[mapData[index]];
                        compareData[index] = mapData[index];
                    }
                });
        }

        private void ticker_Tick(object sender, EventArgs e)
        {
            byte flag = Tick(mapData, playerMoved, (byte)key);
            playerMoved = false;
            updateMap();
            int point = GetPoint();
            labelPoint.Text = "得分：" + point;
            
            if(1 == flag)
            {
                ticker.Stop();
                MessageBox.Show("Game Over!");
                refreshGame();
            }
            else if(point >= pointThreshold)
            {
                ticker.Stop();
                MessageBox.Show("You Win!");
                if(level < MAX_LEVEL)
                {
                    level++;
                    refreshGame();
                }
                else
                {
                    ticker.Stop();
                    MessageBox.Show("你通关了!");
                }
                
                
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ticker.Start();
            btnStart.Enabled = false;
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void FormMain_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Escape:
                    Application.Exit();
                    break;
                case Keys.W:
                    playerMoved = true;
                    this.key = Key.ARROW_UP;
                    break;
                case Keys.S:
                    playerMoved = true;
                    this.key = Key.ARROW_DOWN;
                    break;
                case Keys.A:
                    playerMoved = true;
                    this.key = Key.ARROW_LEFT;
                    break;
                case Keys.D:
                    playerMoved = true;
                    this.key = Key.ARROW_RIGHT;
                    break;
            }
        }

        private void refreshGame()
        {
            btnStart.Enabled = true;
            labelPoint.Text = "得分：0";
            labelLevel.Text = "关卡：" + (level+1);
            Restart(a, b, mapData,(byte)level);
            updateMap();
        }

    }
}
