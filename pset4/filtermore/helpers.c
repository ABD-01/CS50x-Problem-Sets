#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swap;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swapped Red
            swap = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = swap;
            //swapped Green
            swap = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = swap;
            //swapped Blue
            swap = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

        // average of the ORIGINAL value of the pixels around it
        int avgR, avgG, avgB, counter;

        // make a copy of the original image for the calculations

        RGBTRIPLE copy[height][width];

        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                copy[h][w] = image[h][w];
            }
        }

        // go across the image
        for (int pxRow = 0; pxRow < height; pxRow++)
        {
            for (int pxColumn = 0; pxColumn < width; pxColumn++)
            {
                // initialize the variables and reset them to 0
                avgR = 0;
                avgG = 0;
                avgB = 0;
                counter = 0;
                // go across the pixels around
                for (int row = -1; row < 2; row++)
                {
                    for (int column = -1; column < 2; column++)
                    {
                        if (pxRow + row < 0 || pxColumn + column < 0 || pxRow + row >= height || pxColumn + column >= width)
                        {

                        }
                        else
                        {
                            avgR += copy[pxRow + row][pxColumn + column].rgbtRed;
                            avgG += copy[pxRow + row][pxColumn + column].rgbtGreen;
                            avgB += copy[pxRow + row][pxColumn + column].rgbtBlue;
                            counter ++;
                        }
                    }
                }
                image[pxRow][pxColumn].rgbtRed = round(avgR / (float) counter);
                image[pxRow][pxColumn].rgbtGreen = round(avgG / (float) counter);
                image[pxRow][pxColumn].rgbtBlue = round(avgB / (float) counter);
            }
        }

        return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //first a 1-pixel, black frame is added
    RGBTRIPLE temp [height + 2][width + 2];

    for (int i = 0; i < height + 1; i++)
    {
        temp[i][0].rgbtBlue = 0;
        temp[i][0].rgbtGreen = 0;
        temp[i][0].rgbtRed = 0;

        temp[i][width + 1].rgbtBlue = 0;
        temp[i][width + 1].rgbtGreen = 0;
        temp[i][width + 1].rgbtRed = 0;


        for (int j = 0; j < width + 1; j++)
        {
            temp[i + 1][j + 1] = image[i][j];
        }
    }
    for (int i = 0; i < width +1; i++)
    {
        temp[0][i].rgbtBlue = 0;
        temp[0][i].rgbtGreen = 0;
        temp[0][i].rgbtRed = 0;

        temp[height + 1][i].rgbtBlue = 0;
        temp[height + 1][i].rgbtGreen = 0;
        temp[height + 1][i].rgbtRed = 0;
    }

    //copy of temp is made (temp2)
    RGBTRIPLE temp2[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            temp2[i][j] = temp[i][j];
        }
    }


    for (int i = 1; i < height + 1; i++)
    {
        for(int j = 1; j < width + 1; j++)
        {
        //G(x) red
        int numRx = (temp2[i - 1][j - 1].rgbtRed * -1) + (temp2[i - 1][j + 1].rgbtRed * 1) + (temp2[i][j - 1].rgbtRed * -2) + (temp2[i][j + 1].rgbtRed * 2) + (temp2[i + 1][j - 1].rgbtRed * -1) + (temp2[i + 1][j + 1].rgbtRed * 1);
        //G(y) red
        int numRy = (temp2[i - 1][j - 1].rgbtRed * -1) + (temp2[i - 1][j].rgbtRed * - 2) + (temp2[i - 1][j + 1].rgbtRed * - 1) + (temp2[i + 1][j - 1].rgbtRed * 1) + (temp2[i + 1][j].rgbtRed * 2) +  (temp2[i + 1][j + 1].rgbtRed * 1);
        int numR = round(sqrt(pow(numRx, 2) + pow(numRy, 2)));
        temp[i][j].rgbtRed =(numR > 255) ? 255 : numR;
        image[i - 1][j - 1].rgbtRed = temp[i][j].rgbtRed;

        //G(x) blue
        int numBx = (temp2[i - 1][j - 1].rgbtBlue * -1) + (temp2[i - 1][j + 1].rgbtBlue * 1) + (temp2[i][j - 1].rgbtBlue * -2) + (temp2[i][j + 1].rgbtBlue * 2) + (temp2[i + 1][j - 1].rgbtBlue * -1) + (temp2[i + 1][j + 1].rgbtBlue * 1);
        //G(y) blue
        int numBy = (temp2[i - 1][j - 1].rgbtBlue * -1) + (temp2[i - 1][j].rgbtBlue * - 2) + (temp2[i - 1][j + 1].rgbtBlue * - 1) + (temp2[i + 1][j - 1].rgbtBlue * 1) + (temp2[i + 1][j].rgbtBlue * 2) +  (temp2[i + 1][j + 1].rgbtBlue * 1);
        int numB = round(sqrt(pow(numBx, 2) + pow(numBy, 2)));
        temp[i][j].rgbtBlue = (numB > 255) ? 255 : numB;
        image[i - 1][j - 1].rgbtBlue = temp[i][j].rgbtBlue;

        //G(x) green
        int numGx = (temp2[i - 1][j - 1].rgbtGreen * -1) + (temp2[i - 1][j + 1].rgbtGreen * 1) + (temp2[i][j - 1].rgbtGreen * -2) + (temp2[i][j + 1].rgbtGreen * 2) + (temp2[i + 1][j - 1].rgbtGreen * -1) + (temp2[i + 1][j + 1].rgbtGreen * 1);
        //G(y) green
        int numGy = (temp2[i - 1][j - 1].rgbtGreen * -1) + (temp2[i - 1][j].rgbtGreen * - 2) + (temp2[i - 1][j + 1].rgbtGreen * - 1) + (temp2[i + 1][j - 1].rgbtGreen * 1) + (temp2[i + 1][j].rgbtGreen * 2) +  (temp2[i + 1][j + 1].rgbtGreen * 1);
        int numG = round(sqrt(pow(numGx, 2) + pow(numGy, 2)));
        temp[i][j].rgbtGreen = (numG > 255) ? 255 : numG;
        image[i - 1][j - 1].rgbtGreen = temp[i][j].rgbtGreen;

        }
    }

    return;
}