#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // still don't get why BYTE works here but not for the sepia filter.
            BYTE grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Tried with BYTE but didn't work.
            // Figured that question out with a slight hint form discord(Yaaaaaay!!)
            // Just applying the sepia filter values
            int sBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sBlue > 255)
            {
                sBlue = 255;
            }

            int sGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sGreen > 255)
            {
                sGreen = 255;
            }

            int sRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sRed > 255)
            {
                sRed = 255;
            }

            // Adding those new RBG values to the pixel
            image[i][j].rgbtBlue = sBlue;
            image[i][j].rgbtGreen = sGreen;
            image[i][j].rgbtRed = sRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // I initially forgot to put the +1, resulting in impossible arrays
            // And then I forgot the parentheses lmao. Yeah that's not gonna help
            RGBTRIPLE buffer = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // We need to avoid blurring a picture with already blurred neighbouring pixels.
    // That means we need to copy the entire image, so we have a sample to reference while blurring.
    RGBTRIPLE sample[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sample[i][j] = image[i][j];
        }
    }

    // Now to blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Int because we'll be going a lot higher than a BYTE in terms of value
            // Colors will sum up the total values
            // Neighbour counts the total neighbour pixels for later division.
            int blueSum, greenSum, redSum;
            blueSum = greenSum = redSum = 0;
            // had to use float, otherwise got wrong results
            float neighbourSum = 0.0;

            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    int yNow = i + y;
                    int xNow = j + x;

                    //Gotta see if any of the neighbouring pixels are out of the image
                    if (xNow < 0 || yNow < 0 || xNow > (width - 1) || yNow > (height - 1))
                    {
                        // From what I read online about break, it wouldn't work here.
                        // I wanted something that would just skip over the rest of the code and go next.
                        // Welcome my new freind "continue"
                        continue;
                    }
                    blueSum += sample[yNow][xNow].rgbtBlue;
                    greenSum += sample[yNow][xNow].rgbtGreen;
                    redSum += sample[yNow][xNow].rgbtRed;
                    neighbourSum += 1;
                }
            }
            // neighbourSum in float, otherwise int math didn't work out.
            image[i][j].rgbtBlue = round(blueSum / neighbourSum);
            image[i][j].rgbtGreen = round(greenSum /  neighbourSum);
            image[i][j].rgbtRed = round(redSum / neighbourSum);
        }
    }

    return;
}
