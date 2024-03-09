#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int media = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtRed = media;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    float sepiared;
    float sepiagreen;
    float sepiablue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiared = round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189);
            sepiagreen = round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168);
            sepiablue = round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131);
            if (sepiared > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = sepiared;
            }
            if (sepiagreen > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = sepiagreen;
            }
            if (sepiablue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = sepiablue;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int) (width / 2); j++)
        {
            RGBTRIPLE temp;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = temp.rgbtBlue;
            image[i][width - 1 - j].rgbtRed = temp.rgbtRed;
            image[i][width - 1 - j].rgbtGreen = temp.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mirror[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double mediablue[9];
            double mediared[9];
            double mediagreen[9];
            for (int ii = 0; ii < 9; ii++)
            {
                mediablue[ii] = 0;
                mediared[ii] = 0;
                mediagreen[ii] = 0;
            }
            int index = 0;
            int zeros = 0;
            double mdblue = 0;
            double mdgreen = 0;
            double mdred = 0;

            for (int bytei = i - 1; bytei < i + 2; bytei++)
            {
                if (bytei < 0 || bytei >= height)
                {
                    mediablue[index] = 0;
                    mediablue[index + 1] = 0;
                    mediablue[index + 2] = 0;
                    mediagreen[index] = 0;
                    mediagreen[index + 1] = 0;
                    mediagreen[index + 2] = 0;
                    mediared[index] = 0;
                    mediared[index + 1] = 0;
                    mediared[index + 2] = 0;
                    zeros = zeros + 3;
                    index = index + 3;
                }
                else
                {
                    for (int bytej = j - 1; bytej < j + 2; bytej++)
                    {
                        if (bytej < 0 || bytej >= width)
                        {
                            mediablue[index] = 0;
                            mediagreen[index] = 0;
                            mediared[index] = 0;
                            zeros++;
                        }
                        else
                        {
                            mediablue[index] = image[bytei][bytej].rgbtBlue;
                            mediagreen[index] = image[bytei][bytej].rgbtGreen;
                            mediared[index] = image[bytei][bytej].rgbtRed;
                        }
                        index++;
                    }
                }
            }

            for (int ii = 0; ii < 9; ii++)
            {
                mdblue = mdblue + mediablue[ii];
            }
            mdblue = round(mdblue / (9.0 - zeros));
            mirror[i][j].rgbtBlue = mdblue;

            for (int ii = 0; ii < 9; ii++)
            {
                mdgreen = mdgreen + mediagreen[ii];
            }
            mdgreen = round(mdgreen / (9.0 - zeros));
            mirror[i][j].rgbtGreen = mdgreen;

            for (int ii = 0; ii < 9; ii++)
            {
                mdred = mdred + mediared[ii];
            }
            mdred = round(mdred / (9.0 - zeros));
            mirror[i][j].rgbtRed = mdred;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = mirror[i][j].rgbtRed;
            image[i][j].rgbtGreen = mirror[i][j].rgbtGreen;
            image[i][j].rgbtBlue = mirror[i][j].rgbtBlue;
        }
    }
    return;
}

