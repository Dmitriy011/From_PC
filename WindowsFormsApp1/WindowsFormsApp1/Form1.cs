using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Filters_Rozanov;
using System.ComponentModel;
using Test_filter;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Bitmap image;
        public Form1()
        {
            InitializeComponent();
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image files | *.png; *.jpg; *.bmp; | All Files (*.*) | *.*";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                image = new Bitmap(dialog.FileName);
                pictureBox1.Image = image;
                pictureBox1.Refresh();
            }
        }

        private void точечныеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            InvertFilter filter = new InvertFilter();
            Bitmap resultImage = filter.processImage(image);
            pictureBox1.Image = resultImage;
            pictureBox1.Refresh();
        }
        private void размытиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.MotionBlur(image);
            pictureBox1.Image = resultImage;
            //pictureBox1.Refresh();
        }

        private void cдвигToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void серыйМирToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.GrayWorld(image);
            pictureBox1.Image = resultImage;
        }
        private void тиснениеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.Tisnenie_Execute(image);
            pictureBox1.Image = resultImage;
        }
        private void autolevelsToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.Autolevels(image);
            pictureBox1.Image = resultImage;
            
        }

        private void erisonToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.Erison(image);
            pictureBox1.Image = resultImage;
        }

        private void медианныйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap resultImage = Filters_test.Median(image);
            pictureBox1.Image = resultImage;
        }
    }

}

