#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    int tmp;

    i = 0;
    while (i < height)
    {
        j = 0;
        tmp = 0;
        while (j < width)
        {
            tmp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
            j++;
        }
        i++;
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    RGBTRIPLE tmp;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width / 2)
        {
            tmp.rgbtBlue = image[i][j].rgbtBlue;
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            tmp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = tmp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = tmp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = tmp.rgbtRed;
            j++;
        }
        i++;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    RGBTRIPLE tmp[height][width];

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (i == 0 && i != (height - 1))
            {
                if (j == 0 && j != (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                                image[i + 1][j + 1].rgbtBlue) / 4.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                                 image[i + 1][j + 1].rgbtGreen) / 4.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                               image[i + 1][j + 1].rgbtRed) / 4.0);
                }
                else if (j != 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i + 1][j - 1].rgbtBlue) / 4.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i + 1][j - 1].rgbtGreen) / 4.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i + 1][j - 1].rgbtRed) / 4.0);
                }
                else if (j == 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue) / 2.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen) / 2.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed) / 2.0);
                }
                else
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                }
            }
            else if (i != 0 && i == (height - 1))
            {
                if (j == 0 && j != (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                                image[i - 1][j + 1].rgbtBlue) / 4.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                                 image[i - 1][j + 1].rgbtGreen) / 4.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                               image[i - 1][j + 1].rgbtRed) / 4.0);
                }
                else if (j != 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i - 1][j - 1].rgbtBlue) / 4.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i - 1][j - 1].rgbtGreen) / 4.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i - 1][j - 1].rgbtRed) / 4.0);
                }
                else if (j == 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue) / 2.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen) / 2.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed) / 2.0);
                }
                else
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0);
                }
            }
            else if (i == 0 && i == (height - 1))
            {
                if (j == 0 && j != (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 2.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 2.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 2.0);
                }
                else if (j != 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 2.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 2.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed) / 2.0);
                }
                else if (j == 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
                    tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
                    tmp[i][j].rgbtRed = image[i][j].rgbtRed;
                }
                else
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 3.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 3.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 3.0);
                }
            }
            else
            {
                if (j == 0 && j != (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                                image[i + 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                                 image[i + 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                               image[i + 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                }
                else if (j != 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i + 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i + 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i + 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0);
                }
                else if (j == 0 && j == (width - 1))
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue) / 3.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen) / 3.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed) / 3.0);
                }
                else
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + \
                                                image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 9.0);
                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                                 image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + \
                                                 image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 9.0);
                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                               image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + \
                                               image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 9.0);
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            j++;
        }
        i++;
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    int outp;

    typedef struct
    {
        DWORD  rgbtBlue;
        DWORD  rgbtGreen;
        DWORD  rgbtRed;
    } __attribute__((__packed__))
    TMP_LONG;

    TMP_LONG tmpX[height][width];
    TMP_LONG tmpY[height][width];

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            //i == 0, edge
            if (i == 0 && i != (height - 1))
            {
                //edge
                if (j == 0 && j != (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                }
                //edge
                else if (j != 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = - 2 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = - 2 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = - 2 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
                }
                //edge
                else if (j == 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 0;
                    tmpX[i][j].rgbtGreen = 0;
                    tmpX[i][j].rgbtRed = 0;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed;
                }
                else
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue + \
                                          image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen + \
                                           image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed - 2 * image[i][j - 1].rgbtRed + \
                                         image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                }
            }
            // i == (height - 1), edge
            else if (i != 0 && i == (height - 1))
            {
                //edge
                if (j == 0 && j != (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed;
                }
                //edge
                else if (j != 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = - 2 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = - 2 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen ;
                    tmpX[i][j].rgbtRed = - 2 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed ;
                }
                //edge
                else if (j == 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 0;
                    tmpX[i][j].rgbtGreen = 0;
                    tmpX[i][j].rgbtRed = 0;
                    tmpY[i][j].rgbtBlue = - 2 * image[i - 1][j].rgbtBlue;
                    tmpY[i][j].rgbtGreen = - 2 * image[i - 1][j].rgbtGreen ;
                    tmpY[i][j].rgbtRed = - 2 * image[i - 1][j].rgbtRed;
                }
                else
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue + \
                                          image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen + \
                                           image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed - 2 * image[i][j - 1].rgbtRed + \
                                         image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = - 2 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed - image[i - 1][j + 1].rgbtRed;
                }
            }
            // (i == 0 && i == (height - 1)), edge
            else if (i == 0 && i == (height - 1))
            {
                //edge
                if (j == 0 && j != (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 0;
                    tmpY[i][j].rgbtGreen = 0;
                    tmpY[i][j].rgbtRed = 0;
                }
                //edge
                else if (j != 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = - 2 * image[i][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = - 2 * image[i][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = - 2 * image[i][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 0;
                    tmpY[i][j].rgbtGreen = 0;
                    tmpY[i][j].rgbtRed = 0;
                }
                //edge
                else if (j == 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 0;
                    tmpX[i][j].rgbtGreen = 0;
                    tmpX[i][j].rgbtRed = 0;
                    tmpY[i][j].rgbtBlue = 0;
                    tmpY[i][j].rgbtGreen = 0;
                    tmpY[i][j].rgbtRed = 0;
                }
                else
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed - 2 * image[i][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 0;
                    tmpY[i][j].rgbtGreen = 0;
                    tmpY[i][j].rgbtRed = 0;
                }
            }
            // not edge, inside bmp
            else
            {
                //edge
                if (j == 0 && j != (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + \
                                          image[i + 1][j + 1].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + \
                                           image[i + 1][j + 1].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed + \
                                         image[i + 1][j + 1].rgbtRed - image[i - 1][j + 1].rgbtRed;
                }
                //edge
                else if (j != 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = - 2 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = - 2 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = - 2 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + \
                                          image[i + 1][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + \
                                           image[i + 1][j - 1].rgbtGreen- image[i - 1][j - 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed + \
                                         image[i + 1][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed;
                }
                //edge
                else if (j == 0 && j == (width - 1))
                {
                    tmpX[i][j].rgbtBlue = 0;
                    tmpX[i][j].rgbtGreen = 0;
                    tmpX[i][j].rgbtRed = 0;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen - 2 * image[i - 1][j].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed;
                }
                else
                {
                    tmpX[i][j].rgbtBlue = 2 * image[i][j + 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue + \
                                          image[i - 1][j + 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue + \
                                          image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue;
                    tmpX[i][j].rgbtGreen = 2 * image[i][j + 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen + \
                                           image[i - 1][j + 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen + \
                                           image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen;
                    tmpX[i][j].rgbtRed = 2 * image[i][j + 1].rgbtRed - 2 * image[i][j - 1].rgbtRed + \
                                         image[i - 1][j + 1].rgbtRed - image[i - 1][j - 1].rgbtRed + \
                                         image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed;
                    tmpY[i][j].rgbtBlue = 2 * image[i + 1][j].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + \
                                          image[i + 1][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue + \
                                          image[i + 1][j + 1].rgbtBlue - image[i - 1][j + 1].rgbtBlue;
                    tmpY[i][j].rgbtGreen = 2 * image[i + 1][j].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + \
                                           image[i + 1][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen + \
                                           image[i + 1][j + 1].rgbtGreen - image[i - 1][j + 1].rgbtGreen;
                    tmpY[i][j].rgbtRed = 2 * image[i + 1][j].rgbtRed - 2 * image[i - 1][j].rgbtRed + \
                                         image[i + 1][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed + \
                                         image[i + 1][j + 1].rgbtRed - image[i - 1][j + 1].rgbtRed;
                }
            }
            j++;
        }
        i++;
    }
    // update structure values
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            outp = round(sqrt(tmpX[i][j].rgbtBlue * tmpX[i][j].rgbtBlue + tmpY[i][j].rgbtBlue * tmpY[i][j].rgbtBlue));
            if (outp > 255)
            {
                outp = 255;
            }
            image[i][j].rgbtBlue = outp;
            outp = round(sqrt(tmpX[i][j].rgbtGreen * tmpX[i][j].rgbtGreen + tmpY[i][j].rgbtGreen * tmpY[i][j].rgbtGreen));
            if (outp > 255)
            {
                outp = 255;
            }
            image[i][j].rgbtGreen = outp;
            outp = round(sqrt(tmpX[i][j].rgbtRed * tmpX[i][j].rgbtRed + tmpY[i][j].rgbtRed * tmpY[i][j].rgbtRed));
            if (outp > 255)
            {
                outp = 255;
            }
            image[i][j].rgbtRed = outp;
            j++;
        }
        i++;
    }
    return;
}
