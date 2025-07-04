l#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;

            int l = round((b + g + r) / 3);

            // Update pixel values
            image[i][j].rgbtBlue = l;
            image[i][j].rgbtGreen = l;
            image[i][j].rgbtRed = l;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            sepiaRed = (int) round(fmin(sepiaRed, 255.));
            sepiaGreen = (int) round(fmin(sepiaGreen, 255.));
            sepiaBlue = (int) round(fmin(sepiaBlue, 255.));

            // Update pixel values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE row[width];
        int col_backwards = width;
        for (int j = 0; j < width; j++)
        {
            row[col_backwards] = image[i][j];
            col_backwards--;
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j] = row[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int col = 0; col < height; col++)
    {
        for (int row = 0; row < width; row++)
        {

            // buffers for each channel
            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;
            // counter of exisiting surrounding pixels so we can average by it
            double divider = 0;

            for (int i = col - 1; i <= col + 1; i++)
            {
                for (int j = row - 1; j <= row + 1; j++)
                {
                    // If a pixel is within a valid range
                    if ((i >= 0 && i < height) && (j >= 0 && j < width))
                    {
                        sumRed = image[i][j].rgbtRed + sumRed;
                        sumGreen = image[i][j].rgbtGreen + sumGreen;
                        sumBlue = image[i][j].rgbtBlue + sumBlue;
                        divider++;
                    }
                }
            }

            copy[col][row].rgbtRed = round((sumRed / divider));
            copy[col][row].rgbtGreen = round((sumGreen / divider));
            copy[col][row].rgbtBlue = round((sumBlue / divider));
        }
    }

    // Overwrite the orinal image with the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }

    return;
}
