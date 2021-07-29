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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Gx & Gy Kernels (Filters)
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // temporay array to store edges pixels;
    RGBTRIPLE edge_img[height][width];



    /* These 4 loops will take the average of every pixel with its 8 neighbors with these considerations:
       Pixels on Edges : 6 pixels are included and 3 pixels are excluded.
       Pixels on Corners: 4 pixels are included and 5 pixels are excluded.
       Others: 9 pixels are included 0 pixels are excluded.
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red_gx = 0, sum_green_gx = 0,  sum_blue_gx = 0;
            float sum_red_gy = 0, sum_green_gy = 0,  sum_blue_gy = 0;

            for (int row = i - 1; row <= i + 1; row++)
            {

                for (int col = j - 1; col <= j + 1; col++)
                {
                    // sum of the pixel and 8 neighboring pixels for every RGB channel
                    if ((row == - 1) || (row == height) || (col == -1) || (col == width))
                    {
                        continue;
                    }

                    // index for Gx & Gy Kernels
                    int ker_row = row - (i - 1);
                    int ker_col = col - (j - 1);

                    // Sum of RGB with applying Gx Kernel
                    sum_red_gx += image[row][col].rgbtRed * Gx[ker_row][ker_col];
                    sum_green_gx += image[row][col].rgbtGreen * Gx[ker_row][ker_col];
                    sum_blue_gx += image[row][col].rgbtBlue * Gx[ker_row][ker_col];

                    // Sum of RGB with applying Gy Kernel
                    sum_red_gy += image[row][col].rgbtRed * Gy[ker_row][ker_col];
                    sum_green_gy += image[row][col].rgbtGreen * Gy[ker_row][ker_col];
                    sum_blue_gy += image[row][col].rgbtBlue * Gy[ker_row][ker_col];

                }
            }

            // Results after applying both of Gx, Gy
            int red_edge = round(sqrt(pow(sum_red_gx,2) + pow(sum_red_gy,2)));
            int green_edge = round(sqrt(pow(sum_green_gx,2) + pow(sum_green_gy,2)));
            int blue_edge = round(sqrt(pow(sum_blue_gx,2) + pow(sum_blue_gy,2)));

            // If the values above 255 make it sharp 255
            if (red_edge > 255)
            {
                red_edge = 255;
            }

            if (green_edge > 255)
            {
                green_edge = 255;
            }

            if (blue_edge > 255)
            {
                blue_edge = 255;
            }

            // The Final Results
            edge_img[i][j].rgbtRed = red_edge;
            edge_img[i][j].rgbtGreen = green_edge;
            edge_img[i][j].rgbtBlue = blue_edge;
        }

    }

    // converting the actual picture by edge_img temporay array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edge_img[i][j];
        }
    }
    return;
}
