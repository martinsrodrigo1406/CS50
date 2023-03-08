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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }


    int gxArray[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gyArray[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int *gyPtr = &gyArray[0];
    int *gxPtr = &gxArray[0];

    int gxRed;
    int gxGreen;
    int gxBlue;

    int gyRed;
    int gyGreen;
    int gyBlue;

    int minHeightBound;
    int maxWidthBound;
    int maxHeightBound;
    int minWidthBound;

    double divisor = 9.0;

    bool topHeightBound = false;
    bool bottomHeightBound = false;

    bool leftWidthBound = false;
    bool rightWidthBound = false;

    double red = 0;
    double green = 0;
    double blue = 0;

    RGBTRIPLE mat[3][3];

    for(int i = 0; i < height; i++)
    {
            if(i == 0)
            {
                minHeightBound = 0;
                maxHeightBound = i + 1;
                topHeightBound = true;
                bottomHeightBound = false;
            }
            else if(i == (height - 1))
            {
                minHeightBound = i - 1;
                maxHeightBound = i;
                bottomHeightBound = true;
                topHeightBound = false;
            }
            else
            {
                minHeightBound = i - 1;
                maxHeightBound = i + 1;
                topHeightBound = false;
                bottomHeightBound = false;
            }

            for(int j = 0; j < width; j++)
            {
                gxRed = 0;
                gxGreen = 0;
                gxBlue = 0;

                gyRed = 0;
                gyGreen = 0;
                gyBlue = 0;

                red = 0;
                green = 0;
                blue = 0;

                for(int k = 0; k < 3; k++)
                {
                    for(int l = 0; l < 3; l++)
                    {
                        mat[k][l].rgbtRed = 0;
                        mat[k][l].rgbtGreen = 0;
                        mat[k][l].rgbtBlue = 0;
                    }
                }

                if(j == 0)
                {
                    minWidthBound = 0;
                    maxWidthBound = j + 1;
                    leftWidthBound = true;
                    rightWidthBound = false;
                }
                else if(j == (width - 1))
                {
                    minWidthBound = j - 1;
                    maxWidthBound = j;
                    rightWidthBound = true;
                    leftWidthBound = false;
                }
                else
                {
                    minWidthBound = j - 1;
                    maxWidthBound = j + 1;
                    leftWidthBound = false;
                    rightWidthBound = false;
                }


                if(leftWidthBound && topHeightBound)
                {
                    //printf("canto superior esquerdo");

                    for(int z = minHeightBound, x = 1; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 1; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(rightWidthBound && topHeightBound)
                {
                    //printf("canto superior direito");
                    for(int z = minHeightBound, x = 1; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 0; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(leftWidthBound && bottomHeightBound)
                {
                    //printf("canto inferior esquerdo");
                    for(int z = minHeightBound, x = 0; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 1; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(rightWidthBound && bottomHeightBound)
                {
                    //printf("canto inferior direito");
                    for(int z = minHeightBound, x = 0; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 0; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(leftWidthBound)
                {
                    //primeira coluna
                    for(int z = minHeightBound, x = 0; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 1; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(rightWidthBound)
                {
                    //ultima coluna
                    for(int z = minHeightBound, x = 0; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 0; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(topHeightBound)
                {
                    //primeira linha
                    for(int z = minHeightBound, x = 1; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 0; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else if(bottomHeightBound)
                {
                    //ultima linha
                    for(int z = minHeightBound, x = 0; z <= maxHeightBound; z++, x++)
                    {
                        for(int v = minWidthBound, t = 0; v <= maxWidthBound; v++, t++)
                        {
                            mat[x][t] = original[z][v];
                        }
                    }

                    for(int a = 0; a < 3; a++)
                    {
                        for(int b = 0; b < 3; b++)
                        {
                            gxRed += mat[a][b].rgbtRed * (*gxPtr);
                            gxGreen += mat[a][b].rgbtGreen * (*gxPtr);
                            gxBlue += mat[a][b].rgbtBlue * (*gxPtr);

                            gyRed += mat[a][b].rgbtRed * (*gyPtr);
                            gyGreen += mat[a][b].rgbtGreen * (*gyPtr);
                            gyBlue += mat[a][b].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                else
                {
                    for(int z = minHeightBound; z <= maxHeightBound; z++)
                    {
                        for(int v = minWidthBound; v <= maxWidthBound; v++)
                        {
                            gxRed += original[z][v].rgbtRed * (*gxPtr);
                            gxGreen += original[z][v].rgbtGreen * (*gxPtr);
                            gxBlue += original[z][v].rgbtBlue * (*gxPtr);

                            gyRed += original[z][v].rgbtRed * (*gyPtr);
                            gyGreen += original[z][v].rgbtGreen * (*gyPtr);
                            gyBlue += original[z][v].rgbtBlue * (*gyPtr);

                            gyPtr++;
                            gxPtr++;
                        }
                    }
                }
                red = sqrt((gxRed * gxRed) + (gyRed * gyRed));
                green = sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen));        //square root of Gx ^ 2 + Gy ^ 2
                blue = sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue));

                if(red > 255)
                {
                    red = 255;
                }
                if(green > 255)
                {
                    green = 255;
                }
                if(blue > 255)
                {
                    blue = 255;
                }

                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtGreen = round(green);
                image[i][j].rgbtBlue = round(blue);

                gyPtr = &gyArray[0];
                gxPtr = &gxArray[0];
            }
        }
    return;
}
