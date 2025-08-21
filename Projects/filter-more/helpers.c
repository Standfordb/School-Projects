#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            gray = round(gray);
            image[i][j].rgbtBlue = (int)gray;
            image[i][j].rgbtGreen = (int)gray;
            image[i][j].rgbtRed = (int)gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0;
            float blue = 0;
            float green = 0;
            float count = 0.0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        //do nothing
                    }
                    else
                    {
                        blue += copy[i + k][j + l].rgbtBlue;
                        green += copy[i + k][j + l].rgbtGreen;
                        red += copy[i + k][j + l].rgbtRed;
                        count++;
                    }
                }
            }
            blue /= count;
            green /= count;
            red /= count;
            blue = round(blue);
            green = round(green);
            red = round(red);
            image[i][j].rgbtBlue = (int)blue;
            image[i][j].rgbtGreen = (int)green;
            image[i][j].rgbtRed = (int)red;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gxred = 0.0;
            float Gxblue = 0.0;
            float Gxgreen = 0.0;
            float Gyred = 0.0;
            float Gyblue = 0.0;
            float Gygreen = 0.0;
            float green;
            float blue;
            float red;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        Gxblue += 0;
                        Gxgreen += 0;
                        Gxred += 0;
                    }
                    else if (k == 0 && l != 0)
                    {
                        Gxblue += copy[i + k][j + l].rgbtBlue * (l * 2);
                        Gxgreen += copy[i + k][j + l].rgbtGreen * (l * 2);
                        Gxred += copy[i + k][j + l].rgbtRed * (l * 2);
                    }
                    else
                    {
                        Gxblue += copy[i + k][j + l].rgbtBlue  * l;
                        Gxgreen += copy[i + k][j + l].rgbtGreen * l;
                        Gxred += copy[i + k][j + l].rgbtRed * l;
                    }

                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        Gyblue += 0;
                        Gygreen += 0;
                        Gyred += 0;
                    }
                    else if (l == 0 && k != 0)
                    {
                        Gyblue += copy[i + k][j + l].rgbtBlue * (k * 2);
                        Gygreen += copy[i + k][j + l].rgbtGreen * (k * 2);
                        Gyred += copy[i + k][j + l].rgbtRed * (k * 2);
                    }
                    else
                    {
                        Gyblue += copy[i + k][j + l].rgbtBlue * k;
                        Gygreen += copy[i + k][j + l].rgbtGreen * k;
                        Gyred += copy[i + k][j + l].rgbtRed * k;
                    }
                }
            }

            blue = (Gxblue * Gxblue) + (Gyblue * Gyblue);
            blue = sqrt(blue);
            blue = round(blue);
            if (blue > 255)
            {
                blue = 255;
            }

            green = (Gxgreen * Gxgreen) + (Gygreen * Gygreen);
            green = sqrt(green);
            green = round(green);
            if (green > 255)
            {
                green = 255;
            }

            red = (Gxred * Gxred) + (Gyred * Gyred);
            red = sqrt(red);
            red = round(red);
            if (red > 255)
            {
                red = 255;
            }

            image[i][j].rgbtBlue = (int)blue;
            image[i][j].rgbtGreen = (int)green;
            image[i][j].rgbtRed = (int)red;
        }
    }
    return;
}
