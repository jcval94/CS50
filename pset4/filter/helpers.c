#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //float average = (float)sum(originalRed, originalBlue, originalGreen)/ 3;
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //getting average of all colors
            average = (int) round((float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtRed = (average);
            image[i][j].rgbtBlue = (average);
            image[i][j].rgbtGreen = (average);
        }
    }
    return;
}

float min(float x, float y)
{
    if (x > y)
    {
        return y;
    }
    return x;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //applying sepia transormation
            sepiaRed = min(255, round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            sepiaGreen = min(255, round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            sepiaBlue = min(255, round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));
            image[i][j].rgbtRed =  round(sepiaRed);
            image[i][j].rgbtBlue =  round(sepiaBlue);
            image[i][j].rgbtGreen =  round(sepiaGreen);
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int auxiliar_rojo[height][width];
    int auxiliar_azul[height][width];
    int auxiliar_verde[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auxiliar_rojo[i][j] = image[i][j].rgbtRed;
            auxiliar_azul[i][j] = image[i][j].rgbtBlue;
            auxiliar_verde[i][j] = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = auxiliar_rojo[i][width - j - 1];
            image[i][j].rgbtBlue = auxiliar_azul[i][width - j - 1];
            image[i][j].rgbtGreen = auxiliar_verde[i][width - j - 1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float auxiliar_rojo[height][width];
    float auxiliar_azul[height][width];
    float auxiliar_verde[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i != 0 && j != 0 && i != (height - 1) && j != (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                              image[i - 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                              image[i][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 9;

                auxiliar_azul[i][j] = (float)(image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                              image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                              image[i][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 9;

                auxiliar_verde[i][j] = (float)(image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                               image[i - 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                               image[i][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 9;
            }
            if (i == 0 && j > 0 && j < (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                              image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                              image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed) / 6;

                auxiliar_azul[i][j] = (float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                              image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                              image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;

                auxiliar_verde[i][j] = (float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                               image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                               image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;
            }
            if (i == (height - 1) && j > 0 && j < (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i - 1][j].rgbtRed +
                                              image[i][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6;

                auxiliar_azul[i][j] = (float)(image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                                              image[i][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;

                auxiliar_verde[i][j] = (float)(image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                               image[i][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;
            }
            if (i > 0 && i < (height - 1) && j == 0)
            {
                auxiliar_rojo[i][j] = (float)(image[i][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                              image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                                              image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6;

                auxiliar_azul[i][j] = (float)(image[i][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                              image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                              image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6;

                auxiliar_verde[i][j] = (float)(image[i][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                               image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                               image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6;
            }
            if (i > 0 && i < (height - 1) && j == (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                              image[i - 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6;

                auxiliar_azul[i][j] = (float)(image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                              image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6;

                auxiliar_verde[i][j] = (float)(image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                               image[i - 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6;
            }
            if (i == 0 && j == 0)
            {
                auxiliar_rojo[i][j] = (float)(image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4;
                auxiliar_azul[i][j] = (float)(image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4;
                auxiliar_verde[i][j] = (float)(image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4;

            }
            if (i == (height - 1) && j == 0)
            {
                auxiliar_rojo[i][j] = (float)(image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed +
                                              image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed) / 4;
                auxiliar_azul[i][j] = (float)(image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue +
                                              image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue) / 4;
                auxiliar_verde[i][j] = (float)(image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen +
                                               image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen) / 4;

            }
            if (i == 0 && j == (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + image[1][width - 1].rgbtRed +
                                              image[1][width - 2].rgbtRed) / 4;
                auxiliar_azul[i][j] = (float)(image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue +
                                              image[1][width - 2].rgbtBlue) / 4;
                auxiliar_verde[i][j] = (float)(image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen +
                                               image[1][width - 2].rgbtGreen) / 4;

            }
            if (i == (height - 1) && j == (width - 1))
            {
                auxiliar_rojo[i][j] = (float)(image[height - 1][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed +
                                              image[height - 2][width - 1].rgbtRed + image[height - 2][width - 2].rgbtRed) / 4;
                auxiliar_azul[i][j] = (float)(image[height - 1][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue +
                                              image[height - 2][width - 1].rgbtBlue + image[height - 2][width - 2].rgbtBlue) / 4;
                auxiliar_verde[i][j] = (float)(image[height - 1][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen +
                                               image[height - 2][width - 1].rgbtGreen + image[height - 2][width - 2].rgbtGreen) / 4;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = round(auxiliar_rojo[i][j]);
            image[i][j].rgbtBlue = round(auxiliar_azul[i][j]);
            image[i][j].rgbtGreen = round(auxiliar_verde[i][j]);
        }
    }
    return;
}
