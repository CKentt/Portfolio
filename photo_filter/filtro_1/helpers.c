#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mirror[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long media[9];
            long mdx = 0;
            long mdy = 0;
            long temp;


            media[0] = image[i - 1][j - 1].rgbtBlue * -1;
            media[1] = image[i - 1][j].rgbtBlue * 0;
            media[2] = image[i - 1][j + 1].rgbtBlue;
            media[3] = image[i][j - 1].rgbtBlue * -2;
            media[4] = image[i][j].rgbtBlue * 0;
            media[5] = image[i][j + 1].rgbtBlue * 2;
            media[6] = image[i + 1][j - 1].rgbtBlue * -1;
            media[7] = image[i + 1][j].rgbtBlue * 0;
            media[8] = image[i + 1][j + 1].rgbtBlue;

            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdx = mdx + media[mi];
            }

            media[0] = image[i - 1][j - 1].rgbtBlue * -1;
            media[1] = image[i - 1][j].rgbtBlue * -2;
            media[2] = image[i - 1][j + 1].rgbtBlue * -1;
            media[3] = image[i][j - 1].rgbtBlue * 0;
            media[4] = image[i][j].rgbtBlue * 0;
            media[5] = image[i][j + 1].rgbtBlue * 0;
            media[6] = image[i + 1][j - 1].rgbtBlue;
            media[7] = image[i + 1][j].rgbtBlue * 2;
            media[8] = image[i + 1][j + 1].rgbtBlue;


            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdy = mdy + media[mi];
            }

            temp = round(sqrt(mdx * mdx + mdy * mdy));
            mirror[i][j].rgbtBlue = round(sqrt(mdx * mdx + mdy * mdy));
            if (temp > 255)
            {
                mirror[i][j].rgbtBlue = 255;
            }
            else
            {
                mirror[i][j].rgbtBlue = temp;
            }
            mdx = 0;
            mdy = 0;



            media[0] = image[i - 1][j - 1].rgbtRed * -1;
            media[1] = image[i - 1][j].rgbtRed * 0;
            media[2] = image[i - 1][j + 1].rgbtRed;
            media[3] = image[i][j - 1].rgbtRed * -2;
            media[4] = image[i][j].rgbtRed * 0;
            media[5] = image[i][j + 1].rgbtRed * 2;
            media[6] = image[i + 1][j - 1].rgbtRed * -1;
            media[7] = image[i + 1][j].rgbtRed * 0;
            media[8] = image[i + 1][j + 1].rgbtRed;

            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdx = mdx + media[mi];
            }

            media[0] = image[i - 1][j - 1].rgbtRed * -1;
            media[1] = image[i - 1][j].rgbtRed * -2;
            media[2] = image[i - 1][j + 1].rgbtRed * -1;
            media[3] = image[i][j - 1].rgbtRed * 0;
            media[4] = image[i][j].rgbtRed * 0;
            media[5] = image[i][j + 1].rgbtRed * 0;
            media[6] = image[i + 1][j - 1].rgbtRed;
            media[7] = image[i + 1][j].rgbtRed * 2;
            media[8] = image[i + 1][j + 1].rgbtRed;

            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdy = mdy + media[mi];
            }

            temp = round(sqrt(mdx * mdx + mdy * mdy));
            mirror[i][j].rgbtRed = round(sqrt(mdx * mdx + mdy * mdy));
            if (temp > 255)
            {
                mirror[i][j].rgbtRed = 255;
            }
            else
            {
                mirror[i][j].rgbtRed = temp;
            }
            mdx = 0;
            mdy = 0;



            media[0] = image[i - 1][j - 1].rgbtGreen * -1;
            media[1] = image[i - 1][j].rgbtGreen * 0;
            media[2] = image[i - 1][j + 1].rgbtGreen;
            media[3] = image[i][j - 1].rgbtGreen * -2;
            media[4] = image[i][j].rgbtGreen * 0;
            media[5] = image[i][j + 1].rgbtGreen * 2;
            media[6] = image[i + 1][j - 1].rgbtGreen * -1;
            media[7] = image[i + 1][j].rgbtGreen * 0;
            media[8] = image[i + 1][j + 1].rgbtGreen;

            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdx = mdx + media[mi];
            }

            media[0] = image[i - 1][j - 1].rgbtGreen * -1;
            media[1] = image[i - 1][j].rgbtGreen * -2;
            media[2] = image[i - 1][j + 1].rgbtGreen * -1;
            media[3] = image[i][j - 1].rgbtGreen * 0;
            media[4] = image[i][j].rgbtGreen * 0;
            media[5] = image[i][j + 1].rgbtGreen * 0;
            media[6] = image[i + 1][j - 1].rgbtGreen;
            media[7] = image[i + 1][j].rgbtGreen * 2;
            media[8] = image[i + 1][j + 1].rgbtGreen;

            if (i == 0)
            {
                media[0] = 0;
                media[1] = 0;
                media[2] = 0;
            }
            else if (i == height - 1)
            {
                media[6] = 0;
                media[7] = 0;
                media[8] = 0;
            }
            if (j == 0)
            {
                media[0] = 0;
                media[3] = 0;
                media[6] = 0;
            }
            else if (j == width - 1)
            {
                media[2] = 0;
                media[5] = 0;
                media[8] = 0;
            }

            for (int mi = 0; mi < 9; mi++)
            {
                mdy = mdy + media[mi];
            }

            temp = round(sqrt(mdx * mdx + mdy * mdy));
            mirror[i][j].rgbtGreen = round(sqrt(mdx * mdx + mdy * mdy));
            if (temp > 255)
            {
                mirror[i][j].rgbtGreen = 255;
            }
            else
            {
                mirror[i][j].rgbtGreen = temp;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = mirror[i][j].rgbtBlue;
            image[i][j].rgbtRed = mirror[i][j].rgbtRed;
            image[i][j].rgbtGreen = mirror[i][j].rgbtGreen;
        }
    }
    return;
}
