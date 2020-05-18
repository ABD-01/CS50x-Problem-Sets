#include <math.h>
#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769 * (float)image[i][j].rgbtGreen + .189 * (float)image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686 * (float)image[i][j].rgbtGreen + .168 * (float)image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534 * (float)image[i][j].rgbtGreen + .131 * (float)image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255 ;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255 ;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255 ;
            }
            image[i][j].rgbtRed =  sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
    int Red[height][width], Green[height][width], Blue[height][width];
    // For middle pixels
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            Red[i][j] = round((image[i - 1][j - 1].rgbtRed
                            + image[i - 1][j].rgbtRed
                            + image[i - 1][j + 1].rgbtRed
                            + image[i][j - 1].rgbtRed
                            + image[i][j].rgbtRed
                            + image[i][j + 1].rgbtRed
                            + image[i + 1][j - 1].rgbtRed
                            + image[i + 1][j].rgbtRed
                            + image[i + 1][j + 1].rgbtRed) / 9) ;
            Green[i][j] = round((image[i - 1][j - 1].rgbtGreen
                            + image[i - 1][j].rgbtGreen
                            + image[i - 1][j + 1].rgbtGreen
                            + image[i][j - 1].rgbtGreen
                            + image[i][j].rgbtGreen
                            + image[i][j + 1].rgbtGreen
                            + image[i + 1][j - 1].rgbtGreen
                            + image[i + 1][j].rgbtGreen
                            + image[i + 1][j + 1].rgbtGreen) / 9) ;
            Blue[i][j] = round((image[i - 1][j - 1].rgbtBlue
                            + image[i - 1][j].rgbtBlue
                            + image[i - 1][j + 1].rgbtBlue
                            + image[i][j - 1].rgbtBlue
                            + image[i][j].rgbtBlue
                            + image[i][j + 1].rgbtBlue
                            + image[i + 1][j - 1].rgbtBlue
                            + image[i + 1][j].rgbtBlue
                            + image[i + 1][j + 1].rgbtBlue) / 9) ;
        }
    }
    // For First row pixels
    for (int i = 0, j = 1; j < width - 1; j++)
    {
        Red[i][j] = round((image[i][j - 1].rgbtRed
                        + image[i][j].rgbtRed
                        + image[i][j + 1].rgbtRed
                        + image[i + 1][j - 1].rgbtRed
                        + image[i + 1][j].rgbtRed
                        + image[i + 1][j + 1].rgbtRed) / 6) ;
        Green[i][j] = round((image[i][j - 1].rgbtGreen
                        + image[i][j].rgbtGreen
                        + image[i][j + 1].rgbtGreen
                        + image[i + 1][j - 1].rgbtGreen
                        + image[i + 1][j].rgbtGreen
                        + image[i + 1][j + 1].rgbtGreen) / 6) ;
        Blue[i][j] = round((image[i][j - 1].rgbtBlue
                        + image[i][j].rgbtBlue
                        + image[i][j + 1].rgbtBlue
                        + image[i + 1][j - 1].rgbtBlue
                        + image[i + 1][j].rgbtBlue
                        + image[i + 1][j + 1].rgbtBlue) / 6) ;
    }
    // For First column pixels
    for (int j = 0, i = 1; i < height - 1; i++)
    {
        Red[i][j] = round((image[i - 1][j].rgbtRed
                        + image[i - 1][j + 1].rgbtRed
                        + image[i][j].rgbtRed
                        + image[i][j + 1].rgbtRed
                        + image[i + 1][j].rgbtRed
                        + image[i + 1][j + 1].rgbtRed) / 6) ;
        Green[i][j] = round((image[i - 1][j].rgbtGreen
                        + image[i - 1][j + 1].rgbtGreen
                        + image[i][j].rgbtGreen
                        + image[i][j + 1].rgbtGreen
                        + image[i + 1][j].rgbtGreen
                        + image[i + 1][j + 1].rgbtGreen) / 6) ;
        Blue[i][j] = round((image[i - 1][j].rgbtBlue
                        + image[i - 1][j + 1].rgbtBlue
                        + image[i][j].rgbtBlue
                        + image[i][j + 1].rgbtBlue
                        + image[i + 1][j].rgbtBlue
                        + image[i + 1][j + 1].rgbtBlue) / 6) ;
    }
    // For Last column pixels
    for (int j = width - 1, i = 1; i < height - 1; i++)
    {
        Red[i][j] = round((image[i - 1][j].rgbtRed
                        + image[i - 1][j - 1].rgbtRed
                        + image[i][j].rgbtRed
                        + image[i][j - 1].rgbtRed
                        + image[i + 1][j].rgbtRed
                        + image[i + 1][j - 1].rgbtRed) / 6) ;
        Green[i][j] = round((image[i - 1][j].rgbtGreen
                        + image[i - 1][j - 1].rgbtGreen
                        + image[i][j].rgbtGreen
                        + image[i][j - 1].rgbtGreen
                        + image[i + 1][j].rgbtGreen
                        + image[i + 1][j - 1].rgbtGreen) / 6) ;
        Blue[i][j] = round((image[i - 1][j].rgbtBlue
                        + image[i - 1][j - 1].rgbtBlue
                        + image[i][j].rgbtBlue
                        + image[i][j - 1].rgbtBlue
                        + image[i + 1][j].rgbtBlue
                        + image[i + 1][j - 1].rgbtBlue) / 6) ;
    }
    // For Last row pixels
    for (int i = width - 1, j = 1; j < width - 1; j++)
    {
        Red[i][j] = round((image[i][j - 1].rgbtRed
                        + image[i][j].rgbtRed
                        + image[i][j + 1].rgbtRed
                        + image[i - 1][j - 1].rgbtRed
                        + image[i - 1][j].rgbtRed
                        + image[i - 1][j + 1].rgbtRed) / 6) ;
        Green[i][j] = round((image[i][j - 1].rgbtGreen
                        + image[i][j].rgbtGreen
                        + image[i][j + 1].rgbtGreen
                        + image[i - 1][j - 1].rgbtGreen
                        + image[i - 1][j].rgbtGreen
                        + image[i - 1][j + 1].rgbtGreen) / 6) ;
        Blue[i][j] = round((image[i][j - 1].rgbtBlue
                        + image[i][j].rgbtBlue
                        + image[i][j + 1].rgbtBlue
                        + image[i - 1][j - 1].rgbtBlue
                        + image[i - 1][j].rgbtBlue
                        + image[i - 1][j + 1].rgbtBlue) / 6) ;
    }
    // For top-right corner
    Red[0][0] = round((image[0][0].rgbtRed
                    + image[0][1].rgbtRed
                    + image[1][0].rgbtRed
                    + image[1][1].rgbtRed) / 4) ;
    Green[0][0] = round((image[0][0].rgbtGreen
                    + image[0][1].rgbtGreen
                    + image[1][0].rgbtGreen
                    + image[1][1].rgbtGreen) / 4) ;
    Blue[0][0] = round((image[0][0].rgbtBlue
                    + image[0][1].rgbtBlue
                    + image[1][0].rgbtBlue
                    + image[1][1].rgbtBlue) / 4) ;
    // For top-left corner
    Red[0][width - 1] = round((image[0][width - 2].rgbtRed
                            + image[0][width - 1].rgbtRed
                            + image[1][width - 2].rgbtRed
                            + image[1][width - 1].rgbtRed) / 4) ;
    Green[0][width - 1] = round((image[0][width - 2].rgbtGreen
                            + image[0][width - 1].rgbtGreen
                            + image[1][width - 2].rgbtGreen
                            + image[1][width - 1].rgbtGreen) / 4) ;
    Blue[0][width - 1] = round((image[0][width - 2].rgbtBlue
                            + image[0][width - 1].rgbtBlue
                            + image[1][width - 2].rgbtBlue
                            + image[1][width - 1].rgbtBlue) / 4) ;
    // For bottom-right corner
    Red[height - 1][0] = round((image[height - 2][0].rgbtRed
                            + image[height - 1][1].rgbtRed
                            + image[height - 2][0].rgbtRed
                            + image[height - 1][1].rgbtRed) / 4) ;
    Green[height - 1][0] = round((image[height - 2][0].rgbtGreen
                            + image[height - 1][1].rgbtGreen
                            + image[height - 2][0].rgbtGreen
                            + image[height - 1][1].rgbtGreen) / 4) ;
    Blue[height - 1][0] = round((image[height - 2][0].rgbtBlue
                            + image[height - 1][1].rgbtBlue
                            + image[height - 2][0].rgbtBlue
                            + image[height - 1][1].rgbtBlue) / 4) ;
    // For bottom-left corner
    Red[height - 1][width - 1] = round((image[height - 2][width - 2].rgbtRed
                                    + image[height - 2][width - 1].rgbtRed
                                    + image[height - 1][width - 2].rgbtRed
                                    + image[height - 1][width - 1].rgbtRed) / 4) ;
    Green[height - 1][width - 1] = round((image[height - 2][width - 2].rgbtGreen
                                    + image[height - 2][width - 1].rgbtGreen
                                    + image[height - 1][width - 2].rgbtGreen
                                    + image[height - 1][width - 1].rgbtGreen) / 4) ;
    Blue[height - 1][width - 1] = round((image[height - 2][width - 2].rgbtBlue
                                    + image[height - 2][width - 1].rgbtBlue
                                    + image[height - 1][width - 2].rgbtBlue
                                    + image[height - 1][width - 1].rgbtBlue) / 4) ;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed =  Red[i][j];
            image[i][j].rgbtGreen = Green[i][j];
            image[i][j].rgbtBlue = Blue[i][j];
        }
    }

    return;
}
