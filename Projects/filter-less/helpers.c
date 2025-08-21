#include "helpers.h"
#include <math.h>


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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_red = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            int sepia_green = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            int sepia_blue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
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
