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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    int tmpR;
    int tmpG;
    int tmpB;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            tmpR = round(image[i][j].rgbtBlue * 0.189 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtRed * 0.393);
            if (tmpR > 255)
            {
                tmpR = 255;
            }
            tmpG = round(image[i][j].rgbtBlue * 0.168 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtRed * 0.349);
            if (tmpG > 255)
            {
                tmpG = 255;
            }
            tmpB = round(image[i][j].rgbtBlue * 0.131 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtRed * 0.272);
            if (tmpB > 255)
            {
                tmpB = 255;
            }
            image[i][j].rgbtBlue = tmpB;
            image[i][j].rgbtGreen = tmpG;
            image[i][j].rgbtRed = tmpR;
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

/* call it:
* make filter
* ./filter -b images/yard.bmp out.bmp
* ./filter -r images/yard.bmp out.bmp
* ./filter -s images/yard.bmp out.bmp
* ./filter -g images/yard.bmp out.bmp */