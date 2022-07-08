using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;


namespace Filters_Rozanov
{
    abstract class Filters
    {
        public int Clamp(int value, int min, int max)
        {
            if (value < min)
            {
                return min;
            }
            if (value > max)
            {
                return max;
            }

            return value;
        }
        protected abstract Color calculateNewPixelColor(Bitmap sourceImage, int x, int y);
        public Bitmap processImage(Bitmap sourceImage)
        {
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);

            for (int i = 0; i < sourceImage.Width; i++)
            {
                for (int j = 0; j < sourceImage.Height; j++)
                {
                    resultImage.SetPixel(i, j, calculateNewPixelColor(sourceImage, i, j));
                }
            }

            return resultImage;
        }
    }

    class InvertFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            Color resultColor = Color.FromArgb(255 - sourceColor.R, 255 - sourceColor.G, 255 - sourceColor.B);

            return resultColor;
        }
    }
    class MatrixFilter : Filters
    {
        protected float[,] kernel = null;
        protected MatrixFilter() { }
        public MatrixFilter(float[,] kernel)
        {
            this.kernel = kernel;
        }

        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;
            float resultR = 0;
            float resultG = 0;
            float resultB = 0;
            for (int l = -radiusY; l <= radiusY; l++)
                for (int k = -radiusX; k <= radiusX; k++)
                {
                    int idX = Clamp(x + k, 0, sourceImage.Width - 1);
                    int idY = Clamp(y + l, 0, sourceImage.Height - 1);
                    Color neighborColor = sourceImage.GetPixel(idX, idY);
                    resultR += neighborColor.R * kernel[k + radiusX, l + radiusY];
                    resultG += neighborColor.G * kernel[k + radiusX, l + radiusY];
                    resultB += neighborColor.B * kernel[k + radiusX, l + radiusY];
                }

            return Color.FromArgb(Clamp((int)resultR, 0, 255), Clamp((int)resultG, 0, 255), Clamp((int)resultB, 0, 255));
        }
    }

    class BlurFilter : MatrixFilter
    {
        public BlurFilter()
        {
            int sizeX = 3;
            int sizeY = 3;
            kernel = new float[sizeX, sizeY];
            for (int i = 0; i < sizeX; i++)
            {
                for (int j = 0; j < sizeY; j++)
                {
                    kernel[i, j] = 1.0f / (float)(sizeX * sizeY);
                }
            }
        }
    }

    /*
    public class GrayFilte : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            //0.299 * R+0.587*G+0.114*B
            int intensity = Convert.ToInt32(sourceColor.R * 0.299 + sourceColor.G * 0.587 + sourceColor.B * 0.114);
            intensity = Clamp(intensity, 0, 255);
            Color resultColor = Color.FromArgb(intensity, intensity, intensity);
            return resultColor;
        }
    }

    public class SepiaFilte : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color sourceColor = sourceImage.GetPixel(x, y);
            //0.299 * R+0.587*G+0.114*B
            int intensity = Convert.ToInt32(sourceColor.R * 0.299 + sourceColor.G * 0.587 + sourceColor.B * 0.114);
            intensity = Clamp(intensity, 0, 255);
            Color resultColor = Color.FromArgb(intensity, intensity, intensity);
            return resultColor;
        }
    }

    public class TransferFilter : Filters
    {
        protected override Color calculateNewPixelColor(Bitmap sourseImage, int x, int y)
        {
            if (x + 50 > sourseImage.Width - 1)
            {
                return Color.Transparent;
            }

            else
            {
                Color resultColor = sourseImage.GetPixel(x + 50, y);
                return resultColor;
            }
        }
    }

    
    */
}

namespace Test_filter
{
   public class Filters_test
   {
        private static int[,] kernel = null;
        private static int k;
        public static int Clamp(int value, int min, int max)
        {
            if (value < min)
            {
                return min;
            }
            if (value > max)
            {
                return max;
            }

            return value;
        }
        public static Bitmap MotionBlur(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);
            int size = 9;
            float[,] kernel = new float[size, size];
            for (int i = 0; i < size; i++)
            {
                kernel[i, i] = 1.0f / (float)size;
            }

            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    float res_R = 0;
                    float res_G = 0;
                    float res_B = 0;

                    for (int k = -radiusY; k <= radiusY; k++)
                    {
                        for (int z = -radiusX; z <= radiusX; z++)
                        {
                            int x = Clamp(i + z, 0, source.Width - 1);
                            int y = Clamp(j + k, 0, source.Height - 1);
                            Color neightbour_color = source.GetPixel(x, y);
                            res_R = res_R + neightbour_color.R * kernel[z + radiusX, k + radiusY];
                            res_G = res_G + neightbour_color.G * kernel[z + radiusX, k + radiusY];
                            res_B = res_B + neightbour_color.B * kernel[z + radiusX, k + radiusY];
                        }

                        Color res_color;
                        res_color = Color.FromArgb(Clamp((int)res_R, 0, 255), Clamp((int)res_G, 0, 255), Clamp((int)res_B, 0, 255));
                        resultImage.SetPixel(i, j, res_color);
                    }
                }
            }

            return resultImage;
        }

        public static Bitmap GrayWorld(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);

            double tmp_R = 0;
            double tmp_G = 0;
            double tmp_B = 0;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    tmp_R = tmp_R + source.GetPixel(i, j).R;
                    tmp_G = tmp_G + source.GetPixel(i, j).G;
                    tmp_B = tmp_B + source.GetPixel(i, j).B;
                }
            }
            tmp_R = tmp_R / (source.Width * source.Height);
            tmp_G = tmp_G / (source.Width * source.Height);
            tmp_B = tmp_B / (source.Width * source.Height);
            double AVG = (tmp_R + tmp_G + tmp_B) / 3;

            for (int i = 0; i < source.Width; i++)
            {
                double res_R = 0;
                double res_G = 0;
                double res_B = 0;

                for (int j = 0; j < source.Height; j++)
                {
                    res_R = AVG * source.GetPixel(i, j).R / (tmp_R);
                    res_G = AVG * source.GetPixel(i, j).G / (tmp_G);
                    res_B = AVG * source.GetPixel(i, j).B / (tmp_B);

                    Color res_color;
                    res_color = Color.FromArgb(Clamp((int)res_R, 0, 255), Clamp((int)res_G, 0, 255), Clamp((int)res_B, 0, 255));
                    resultImage.SetPixel(i, j, res_color);
                }
            }

            return resultImage;
        }

        public static Bitmap GrayScaleExecute(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);
            Color sourceColor, resultColor;
            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    sourceColor = source.GetPixel(i, j);
                    resultColor = Color.FromArgb((int)(0.299 * sourceColor.R + 0.587 * sourceColor.G + 0.114 * sourceColor.B),
                    (int)(0.299 * sourceColor.R + 0.587 * sourceColor.G + 0.114 * sourceColor.B),
                    (int)(0.299 * sourceColor.R + 0.587 * sourceColor.G + 0.114 * sourceColor.B));
                    resultImage.SetPixel(i, j, resultColor);
                }
            }
            return resultImage;
        }

        public static Bitmap BrightnessExecute(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);
            Color sourceColor, resultColor;
            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    sourceColor = source.GetPixel(i, j);
                    resultColor = Color.FromArgb(Clamp(sourceColor.R + k, 0, 255),
                    Clamp(sourceColor.G + k, 0, 255),
                    Clamp(sourceColor.B + k, 0, 255));
                    resultImage.SetPixel(i, j, resultColor);
                }
            }
            return resultImage;
        }

        public static Bitmap Tisnenie_Execute(Bitmap source)
        {
            Bitmap image = source;
            int[,] kernelFilter = { { 0, 1, 0 }, { -1, 0, 1 }, { 0, -1, 0 } };
            kernel = kernelFilter;
            Bitmap resultImage = new Bitmap(source.Width, source.Height);
            Color resultColor;

            for (int x = 0; x < source.Width; x++)
            {
                for (int y = 0; y < source.Height; y++)
                {
                    int radiusX = kernel.GetLength(0) / 2;
                    int radiusY = kernel.GetLength(1) / 2;
                    double resultR = 0;
                    double resultG = 0;
                    double resultB = 0;
                    int idX, idY;
                    Color sourceColor;

                    for (int i = -radiusX; i <= radiusX; i++)
                    {
                        for (int j = -radiusY; j <= radiusY; j++)
                        {
                            idX = Clamp(x + i, 0, image.Width - 1);
                            idY = Clamp(y + j, 0, image.Height - 1);
                            sourceColor = image.GetPixel(idX, idY);
                            resultR += sourceColor.R * kernel[i + radiusX, j + radiusY];
                            resultG += sourceColor.G * kernel[i + radiusX, j + radiusY];
                            resultB += sourceColor.B * kernel[i + radiusX, j + radiusY];
                        }
                    }

                    resultColor =  Color.FromArgb(Clamp((int)resultR, 0, 255),  Clamp((int)resultG, 0, 255), Clamp((int)resultB, 0, 255));
                    resultImage.SetPixel(x, y, resultColor);
                }
            }

            k = 100;
            resultImage = GrayScaleExecute(resultImage);
            resultImage = BrightnessExecute(resultImage);
            return resultImage;
        }

        public static Bitmap Autolevels(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);

            float min_R = 255;
            float min_G = 255;
            float min_B = 255;
            float max_R = 0;
            float max_G = 0;
            float max_B = 0;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    if (min_R >= source.GetPixel(i, j).R)
                    {
                        min_R = source.GetPixel(i, j).R;
                    }
                    if (max_R < source.GetPixel(i, j).R)
                    {
                        max_R = source.GetPixel(i, j).R;
                    }

                    if (min_G >= source.GetPixel(i, j).G)
                    {
                        min_G = source.GetPixel(i, j).G;
                    }
                    if (max_G < source.GetPixel(i, j).G)
                    {
                        max_G = source.GetPixel(i, j).G;
                    }

                    if (min_B >= source.GetPixel(i, j).B)
                    {
                        min_B = source.GetPixel(i, j).B;
                    }
                    if (max_B < source.GetPixel(i, j).B)
                    {
                        max_B = source.GetPixel(i, j).B;
                    } 
                }
            }

            for (int i = 0; i < source.Width; i++)
            {
                float res_R = 0;
                float res_G = 0;
                float res_B = 0;

                for (int j = 0; j < source.Height; j++)
                {
                    res_R = (source.GetPixel(i, j).R - min_R) * 255.0f / (max_R - min_R);
                    res_G = (source.GetPixel(i, j).G - min_G) * 255.0f / (max_G - min_G);
                    res_B = (source.GetPixel(i, j).B - min_B) * 255.0f / (max_B - min_B);
  
                    Color res_color;
                    res_color = Color.FromArgb((int)res_R, (int)res_G, (int)res_B);
                    resultImage.SetPixel(i, j, res_color);
                }
            }

            return resultImage;
        }

        public static Bitmap Ideal_reflector(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);

            double min_R = 255;
            double min_G = 255;
            double min_B = 255;
            double max_R = 0;
            double max_G = 0;
            double max_B = 0;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    if (max_R < source.GetPixel(i, j).R)
                    {
                        max_R = source.GetPixel(i, j).R;
                    }
                    if (max_G < source.GetPixel(i, j).G)
                    {
                        max_G = source.GetPixel(i, j).G;
                    }
                    if (max_B < source.GetPixel(i, j).B)
                    {
                        max_B = source.GetPixel(i, j).B;
                    }
                }
            }

            for (int i = 0; i < source.Width; i++)
            {
                double res_R = 0;
                double res_G = 0;
                double res_B = 0;

                for (int j = 0; j < source.Height; j++)
                {
                    res_R = source.GetPixel(i, j).R * 255 / (max_R);
                    res_G = source.GetPixel(i, j).G * 255 / (max_G);
                    res_B = source.GetPixel(i, j).B * 255 / (max_B);

                    Color res_color;
                    res_color = Color.FromArgb(Clamp((int)res_R, 0, 255), Clamp((int)res_G, 0, 255), Clamp((int)res_B, 0, 255));
                    resultImage.SetPixel(i, j, res_color);
                }
            }

            return resultImage;
        }

        public static Bitmap Erison(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);

            int size = 3;
            float[,] kernel = new float[size, size];
            kernel[0, 0] = 0.0f;
            kernel[0, 1] = 1.0f;
            kernel[0, 2] = 0.0f;
            kernel[1, 0] = 1.0f;
            kernel[1, 1] = 1.0f;
            kernel[1, 2] = 1.0f;
            kernel[2, 0] = 0.0f;
            kernel[2, 1] = 1.0f;
            kernel[2, 2] = 0.0f;

            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    Color res_color;
                    res_color = Color.White;
                    byte min = 255;

                    for (int k = -radiusX; k <= radiusX; k++)
                    {
                        for (int z = -radiusY; z <= radiusY; z++)
                        {
                            int x_tmp = Clamp(i + z, 0, source.Width - 1);
                            int y_tmp = Clamp(j + k, 0, source.Height - 1);
                            Color old_color = source.GetPixel(x_tmp, y_tmp);
                            int intensity = old_color.R;
                            if (old_color.R != old_color.G || old_color.R != old_color.B || old_color.G != old_color.B)
                            {
                                intensity = (int)(0.36 * old_color.R + 0.53 * old_color.G + 0.11 * old_color.B);
                            }
                            if (kernel[z + radiusX, k + radiusY] > 0 && intensity < min)
                            {
                                min = (byte)intensity;
                                res_color = old_color;
                            }
                        }
                    }

                    resultImage.SetPixel(i, j, res_color);
                }
            }


            return resultImage;
        }

        public static Bitmap Extension(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);
            int size = 3;
            float[,] kernel = new float[size, size];
            kernel[0, 0] = 0.0f;
            kernel[0, 1] = 1.0f;
            kernel[0, 2] = 0.0f;
            kernel[1, 0] = 1.0f;
            kernel[1, 1] = 1.0f;
            kernel[1, 2] = 1.0f;
            kernel[2, 0] = 0.0f;
            kernel[2, 1] = 1.0f;
            kernel[2, 2] = 0.0f;

            int radiusX = kernel.GetLength(0) / 2;
            int radiusY = kernel.GetLength(1) / 2;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    Color res_color;
                    res_color = Color.Black;
                    byte max = 0;

                    for (int k = -radiusX; k <= radiusX; k++)
                    {
                        for (int z = -radiusY; z <= radiusY; z++)
                        {
                            int x_tmp = Clamp(i + z, 0, source.Width - 1);
                            int y_tmp = Clamp(j + k, 0, source.Height - 1);
                            Color old_color = source.GetPixel(x_tmp, y_tmp);
                            int intensity = old_color.R;
                            if (old_color.R != old_color.G || old_color.R != old_color.B || old_color.G != old_color.B)
                            {
                                intensity = (int)(0.36 * old_color.R + 0.53 * old_color.G + 0.11 * old_color.B);
                            }
                            if (kernel[z + radiusX, k + radiusY] == 1 && intensity > max)
                            {
                                max = (byte)intensity;
                                res_color = old_color;
                            }
                        }
                    }

                    resultImage.SetPixel(i, j, res_color);
                }
            }


            return resultImage;
        }
        public static Bitmap Execute(Bitmap source)
        {
            Bitmap result = new Bitmap(source.Width, source.Height);

            float[,] Gx = new float[3, 3];
            Gx[0, 0] = -1.0f;
            Gx[0, 1] = 0.0f;
            Gx[0, 2] = 1.0f;
            Gx[1, 0] = -2.0f;
            Gx[1, 1] = 0.0f;
            Gx[1, 2] = 2.0f;
            Gx[2, 0] = -1.0f;
            Gx[2, 1] = 0.0f;
            Gx[2, 2] = 1.0f;

            float[,] Gy = new float[3, 3];
            Gy[0, 0] = -1.0f; 
            Gy[0, 1] = -2.0f;
            Gy[0, 2] = -1.0f;
            Gy[1, 0] = 0.0f; 
            Gy[1, 1] = 0.0f;
            Gy[1, 2] = 0.0f;
            Gy[2, 0] = 1.0f;
            Gy[2, 1] = 2.0f; 
            Gy[2, 2] = 1.0f;

            for (int i = 0; i < source.Width; i++)
                for (int j = 0; j < source.Height; j++)
                {

                    int radiusX_x = Gx.GetLength(0) / 2;
                    int radiusY_x = Gx.GetLength(1) / 2;
                    float resultR_x = 0;
                    float resultG_x = 0;
                    float resultB_x = 0;
                    for (int l = -radiusY_x; l <= radiusX_x; l++)
                    { 
                        for (int k = -radiusX_x; k <= radiusY_x; k++)
                        {
                            int tmp_x = Clamp(i + k, 0, source.Width - 1);
                            int tmp_y = Clamp(j + l, 0, source.Height - 1);
                            Color neighborColor = source.GetPixel(tmp_x, tmp_y);
                            resultR_x += neighborColor.R * Gx[k + radiusX_x, l + radiusY_x];
                            resultG_x += neighborColor.G * Gx[k + radiusX_x, l + radiusY_x];
                            resultB_x += neighborColor.B * Gx[k + radiusX_x, l + radiusY_x];
                        }
                    }


                    int radiusX_y = Gy.GetLength(0) / 2;
                    int radiusY_y = Gy.GetLength(1) / 2;
                    float resultR_y = 0;
                    float resultG_y = 0;
                    float resultB_y = 0;
                    for (int l = -radiusY_y; l <= radiusX_y; l++)
                    {     
                        for (int k = -radiusX_y; k <= radiusY_y; k++)
                        {
                            int tmp_x = Clamp(i + k, 0, source.Width - 1);
                            int tmp_y = Clamp(j + l, 0, source.Height - 1);
                            Color neighborColor = source.GetPixel(tmp_x, tmp_y);
                            resultR_y += neighborColor.R * Gy[k + radiusX_x, l + radiusY_x];
                            resultG_y += neighborColor.G * Gy[k + radiusX_x, l + radiusY_x];
                            resultB_y += neighborColor.B * Gy[k + radiusX_x, l + radiusY_x];
                        }
                    }

                    Color newPixel = Color.FromArgb( Clamp((int)Math.Sqrt(resultR_x * resultR_x + resultR_y * resultR_y), 0, 255), Clamp((int)Math.Sqrt(resultG_x * resultG_x + resultG_y * resultG_y), 0, 255), Clamp((int)Math.Sqrt(resultB_x * resultB_x + resultB_y * resultB_y), 0, 255));

                    result.SetPixel(i, j, newPixel);
                }
            
            return result;
        }

        public static Bitmap Median(Bitmap source)
        {
            Bitmap resultImage = new Bitmap(source.Width, source.Height);

            Color sourceColor, resultColor;
            float[] arrayR = new float[9];
            float[] arrayG = new float[9];
            float[] arrayB = new float[9];
            int tmp_x, tmp_y;

            for (int i = 0; i < source.Width; i++)
            {
                for (int j = 0; j < source.Height; j++)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int z = -1; z <= 1; z++)
                        {
                            tmp_x = Clamp(i + k, 0, source.Width - 1);
                            tmp_y = Clamp(j + z, 0, source.Height - 1);
                            sourceColor = source.GetPixel(tmp_x, tmp_y);

                            arrayR[1 + k + 3 * (1 + z)] = sourceColor.R;
                            arrayG[1 + k + 3 * (1 + z)] = sourceColor.G;
                            arrayB[1 + k + 3 * (1 + z)] = sourceColor.B;
                        }
                    }

                    Array.Sort(arrayR);
                    Array.Sort(arrayG);
                    Array.Sort(arrayB);
                    resultColor = Color.FromArgb((int)arrayR[9 / 2], (int)arrayG[9 / 2], (int)arrayB[9 / 2]);
                    resultImage.SetPixel(i, j, resultColor);
                }
            }

            return resultImage;
        }
    }
}
