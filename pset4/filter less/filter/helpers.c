#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            double floatPixel = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;

            int grayPixel = round(floatPixel / 3);

            image[h][w].rgbtBlue = grayPixel;
            image[h][w].rgbtGreen = grayPixel;
            image[h][w].rgbtRed = grayPixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double sepiaRed;
    double sepiaGreen;
    double sepiaBlue;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            for(int i = 0; i < (width - w) - 1; i++)
            {
                RGBTRIPLE temp;
                temp = image[h][i];
                image[h][i] = image[h][i + 1];
                image[h][i + 1] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }

    int redBlur = 0;
    int greenBlur = 0;
    int blueBlur = 0;

    int minHeightBound;
    int maxWidthBound;
    int maxHeightBound;
    int minWidthBound;

    double divisor = 9.0;

    bool atHeightBound = true;
    bool atWidthBound = true;

    for(int n = 0; n < height; n++)
    {
            if(n == 0)
            {
                minHeightBound = 0;
                maxHeightBound = n + 1;
                atHeightBound = true;
            }
            else if(n == (height - 1))
            {
                minHeightBound = n - 1;
                maxHeightBound = n;
                atHeightBound = true;
            }
            else
            {
                minHeightBound = n - 1;
                maxHeightBound = n + 1;
                atHeightBound = false;
            }


            for(int i = 0; i < width; i++)
            {
                redBlur = 0;
                greenBlur = 0;
                blueBlur = 0;

                if(i == 0)
                {
                    minWidthBound = 0;
                    maxWidthBound = i + 1;
                    atWidthBound = true;
                }
                else if(i == (width - 1))
                {
                    minWidthBound = i - 1;
                    maxWidthBound = i;
                    atWidthBound = true;
                }
                else
                {
                    minWidthBound = i - 1;
                    maxWidthBound = i + 1;
                    atWidthBound = false;
                }


                if(atWidthBound && atHeightBound)
                {
                    divisor = 4.0;
                }
                else if(atWidthBound || atHeightBound)
                {
                    divisor = 6.0;
                }
                else
                {
                    divisor = 9.0;
                }


                for(int z = minHeightBound; z <= maxHeightBound; z++)
                {
                    for(int j = minWidthBound; j <= maxWidthBound; j++)
                    {
                        redBlur += original[z][j].rgbtRed;
                        greenBlur += original[z][j].rgbtGreen;
                        blueBlur += original[z][j].rgbtBlue;
                    }
                }

                image[n][i].rgbtBlue = round(blueBlur / divisor);
                image[n][i].rgbtGreen = round(greenBlur / divisor);
                image[n][i].rgbtRed = round(redBlur / divisor);
            }
        }
    return;
}
