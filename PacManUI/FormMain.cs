using System;
using System.Collections.Generic;
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
        AGENT_SIMPLE_FAST,
        AGENT_SIMPLE_SLOW,
        AGENT_SMART_FAST,
        AGENT_SMART_SLOW
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
        private readonly int a = 10;
        private readonly int b = 10;
        private PictureBox[] picMap;
        private int[] mapData;
        private readonly Image[] mapImage = {
            UIResource.EMPTY,
            UIResource.WALL,
            UIResource.CANDY
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

            //initialize public variables
            picMap = new PictureBox[a * b];
            mapData = new int[a * b];


            //add picture box on the form
            int topInit = 62, leftInit = 62,step = 30;
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
                        Image = UIResource._1,
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
            GetNewMap(a, b, mapData);
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

        [DllImport("PacManCore.dll")]
        private static extern void GetNewMap(int a, int b, int[] data);

    }
}
