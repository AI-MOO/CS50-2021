#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtBlue = average_value;

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
            // Aplying sepia algorithm for every pixel in the picture
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // for all values greater than 0xFF (255) make it exactly 0xFF (255)
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // converting the actual pixel by sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }

    }





    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Array to store one half of the picture's pixels!
    RGBTRIPLE temp[height][width];

    // Taking one half of the picture
    int index = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < index; j++)
        {
            // store one half of the picture in the temp array
            temp[i][j] = image[i][j];
            // flip the second half and store it in the first one
            image[i][j] = image[i][width - 1 - j];
            // store the first half in the second one
            image[i][width - 1 - j] = temp[i][j];
        }

    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // temporay array to store blured pixels;
    RGBTRIPLE Blured_Image[height][width];

    /* These 4 loops will take the average of every pixel with its 8 neighbors with these considerations:
       Pixels on Edges : 6 pixels are included and 3 pixels are excluded.
       Pixels on Corners: 4 pixels are included and 5 pixels are excluded.
       Others: 9 pixels are included 0 pixels are excluded.
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0, sum_green = 0,  sum_blue = 0, covered_pixels = 0;
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    // execlude non existing pixels for edges and corners
                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        continue;
                    }

                    // sum of the pixel and 8 neighboring pixels for every RGB channel
                    sum_red += image[row][col].rgbtRed;
                    sum_green += image[row][col].rgbtGreen;
                    sum_blue += image[row][col].rgbtBlue;
                    covered_pixels++;

                }
            }

            // The average of the pixel and 8 neighboring pixels for every RGB channel
            Blured_Image[i][j].rgbtRed = round(sum_red / (float)covered_pixels);
            Blured_Image[i][j].rgbtGreen = round(sum_green / (float)covered_pixels);
            Blured_Image[i][j].rgbtBlue = round(sum_blue / (float)covered_pixels);

        }

    }

    // converting the actual picture by blured temporay array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = Blured_Image[i][j];
        }
    }

}