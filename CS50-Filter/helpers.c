#include "helpers.h"
#include <math.h>
#include <stdio.h>

int min(int x, int y)
{
    if (y > x)
    {
        return x;
    }
    return y;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int gray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0);
            image[j][i].rgbtBlue = gray;
            image[j][i].rgbtGreen = gray;
            image[j][i].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            RGBTRIPLE original = image[j][i];
            int sepiaBlue = round(.272 * original.rgbtRed + .534 * original.rgbtGreen + .131 * original.rgbtBlue);
            int sepiaGreen = round(.349 * original.rgbtRed + .686 * original.rgbtGreen + .168 * original.rgbtBlue);
            int sepiaRed = round(.393 * original.rgbtRed + .769 * original.rgbtGreen + .189 * original.rgbtBlue);
            image[j][i].rgbtBlue = min(255, sepiaBlue);
            image[j][i].rgbtGreen = min(255, sepiaGreen);
            image[j][i].rgbtRed = min(255, sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE og_image[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            og_image[j][i] = image[j][i];
        }
    }


    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i == 0 && j == 0) //top left corner
            {
                image[j][i].rgbtRed = round((og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed + \
                                       og_image[j+1][i].rgbtRed + \
                                       og_image[j+1][i+1].rgbtRed) / 4.0);
                image[j][i].rgbtGreen = round((og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen + \
                                       og_image[j+1][i].rgbtGreen + \
                                       og_image[j+1][i+1].rgbtGreen) / 4.0);
                image[j][i].rgbtBlue = round((og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue + \
                                       og_image[j+1][i].rgbtBlue + \
                                       og_image[j+1][i+1].rgbtBlue) / 4.0);
                continue;
            }
            if (i == width - 1 && j == 0) //top right corner
            {
                image[j][i].rgbtRed = round((og_image[j][i-1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j+1][i-1].rgbtRed + \
                                       og_image[j+1][i].rgbtRed) / 4.0);
                image[j][i].rgbtGreen = round((og_image[j][i-1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j+1][i-1].rgbtGreen + \
                                       og_image[j+1][i].rgbtGreen) / 4.0);
                image[j][i].rgbtBlue = round((og_image[j][i-1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j+1][i-1].rgbtBlue + \
                                       og_image[j+1][i].rgbtBlue) / 4.0);
                continue;
            }
            if (i == 0 && j == height - 1) // bottom left corner
            {
                image[j][i].rgbtRed = round((og_image[j-1][i].rgbtRed + \
                                       og_image[j-1][i+1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed) / 4.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i].rgbtGreen + \
                                       og_image[j-1][i+1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen) / 4.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i].rgbtBlue + \
                                       og_image[j-1][i+1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue) / 4.0);
                continue;
            }
            if (i == width - 1 && j == height - 1) //bottom right corner
            {
                image[j][i].rgbtRed = round((og_image[j-1][i-1].rgbtRed + \
                                       og_image[j-1][i].rgbtRed + \
                                       og_image[j][i-1].rgbtRed + \
                                       og_image[j][i].rgbtRed) / 4.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i-1].rgbtGreen + \
                                       og_image[j-1][i].rgbtGreen + \
                                       og_image[j][i-1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen) / 4.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i-1].rgbtBlue + \
                                       og_image[j-1][i].rgbtBlue + \
                                       og_image[j][i-1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue) / 4.0);
                continue;
            }
            if (j == 0) //top row
            {
                image[j][i].rgbtRed = round((og_image[j][i-1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed + \
                                       og_image[j+1][i-1].rgbtRed + \
                                       og_image[j+1][i].rgbtRed + \
                                       og_image[j+1][i+1].rgbtRed) / 6.0);
                image[j][i].rgbtGreen = round((og_image[j][i-1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen + \
                                       og_image[j+1][i-1].rgbtGreen + \
                                       og_image[j+1][i].rgbtGreen + \
                                       og_image[j+1][i+1].rgbtGreen) / 6.0);
                image[j][i].rgbtBlue = round((og_image[j][i-1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue + \
                                       og_image[j+1][i-1].rgbtBlue + \
                                       og_image[j+1][i].rgbtBlue + \
                                       og_image[j+1][i+1].rgbtBlue) / 6.0);
                continue;
            }
            if (j == height - 1) //bottom row
            {
                image[j][i].rgbtRed = round((og_image[j-1][i-1].rgbtRed + \
                                       og_image[j-1][i].rgbtRed + \
                                       og_image[j-1][i+1].rgbtRed + \
                                       og_image[j][i-1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed) / 6.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i-1].rgbtGreen + \
                                       og_image[j-1][i].rgbtGreen + \
                                       og_image[j-1][i+1].rgbtGreen + \
                                       og_image[j][i-1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen) / 6.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i-1].rgbtBlue + \
                                       og_image[j-1][i].rgbtBlue + \
                                       og_image[j-1][i+1].rgbtBlue + \
                                       og_image[j][i-1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue) / 6.0);
                continue;
            }
            if (i == width - 1) // right column
            {
                image[j][i].rgbtRed = round((og_image[j-1][i-1].rgbtRed + \
                                   og_image[j-1][i].rgbtRed + \
                                   og_image[j][i-1].rgbtRed + \
                                   og_image[j][i].rgbtRed + \
                                   og_image[j+1][i-1].rgbtRed + \
                                   og_image[j+1][i].rgbtRed) / 6.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i-1].rgbtGreen + \
                                   og_image[j-1][i].rgbtGreen + \
                                   og_image[j][i-1].rgbtGreen + \
                                   og_image[j][i].rgbtGreen + \
                                   og_image[j+1][i-1].rgbtGreen + \
                                   og_image[j+1][i].rgbtGreen) / 6.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i-1].rgbtBlue + \
                                   og_image[j-1][i].rgbtBlue + \
                                   og_image[j][i-1].rgbtBlue + \
                                   og_image[j][i].rgbtBlue + \
                                   og_image[j+1][i-1].rgbtBlue + \
                                   og_image[j+1][i].rgbtBlue) / 6.0);
                continue;
            }
            if (i == 0) //left column
            {
                image[j][i].rgbtRed = round((og_image[j-1][i].rgbtRed + \
                                       og_image[j-1][i+1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed + \
                                       og_image[j+1][i].rgbtRed + \
                                       og_image[j+1][i+1].rgbtRed) / 6.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i].rgbtGreen + \
                                       og_image[j-1][i+1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen + \
                                       og_image[j+1][i].rgbtGreen + \
                                       og_image[j+1][i+1].rgbtGreen) / 6.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i].rgbtBlue + \
                                       og_image[j-1][i+1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue + \
                                       og_image[j+1][i].rgbtBlue + \
                                       og_image[j+1][i+1].rgbtBlue) / 6.0);
                continue;
            }
            else // middle
            {
                image[j][i].rgbtRed = round((og_image[j-1][i-1].rgbtRed + \
                                       og_image[j-1][i].rgbtRed + \
                                       og_image[j-1][i+1].rgbtRed + \
                                       og_image[j][i-1].rgbtRed + \
                                       og_image[j][i].rgbtRed + \
                                       og_image[j][i+1].rgbtRed + \
                                       og_image[j+1][i-1].rgbtRed + \
                                       og_image[j+1][i].rgbtRed + \
                                       og_image[j+1][i+1].rgbtRed) / 9.0);
                image[j][i].rgbtGreen = round((og_image[j-1][i-1].rgbtGreen + \
                                       og_image[j-1][i].rgbtGreen + \
                                       og_image[j-1][i+1].rgbtGreen + \
                                       og_image[j][i-1].rgbtGreen + \
                                       og_image[j][i].rgbtGreen + \
                                       og_image[j][i+1].rgbtGreen + \
                                       og_image[j+1][i-1].rgbtGreen + \
                                       og_image[j+1][i].rgbtGreen + \
                                       og_image[j+1][i+1].rgbtGreen) / 9.0);
                image[j][i].rgbtBlue = round((og_image[j-1][i-1].rgbtBlue + \
                                       og_image[j-1][i].rgbtBlue + \
                                       og_image[j-1][i+1].rgbtBlue + \
                                       og_image[j][i-1].rgbtBlue + \
                                       og_image[j][i].rgbtBlue + \
                                       og_image[j][i+1].rgbtBlue + \
                                       og_image[j+1][i-1].rgbtBlue + \
                                       og_image[j+1][i].rgbtBlue + \
                                       og_image[j+1][i+1].rgbtBlue) / 9.0);
            }

        }
    }
    return;
}
