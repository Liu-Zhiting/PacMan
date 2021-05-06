using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PacManUI
{
    public partial class FormMain : Form
    {
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
            int n = 10,topInit = 62, leftInit = 62,step = 30;
            PictureBox picTmp;
            for(int i = 0;i < n;i++)
            {
                for(int j = 0; j < n;j++)
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
                }
            }

            //resume layout
            ResumeLayout(false);
        }

        private void FormMain_Load(object sender, EventArgs e)
        {

        }
    }
}
