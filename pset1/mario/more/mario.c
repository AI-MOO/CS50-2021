#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        // prompt the hight from user
        h = get_int("Hight: ");
    }
    while (h < 1 | h > 8);



    int w = 1;
    int x = h;

    // Number of rows loop
    for (int i = 1; i <= h ; i++)
    {
        // Spaces for First Pyramid
        for (int space = 1; space < x; space++)
        {
            printf(" ");
        }

        // First Pyramid
        for (int hash = 0; hash < w; hash++)
        {
            printf("#");
        }

        // Spaces between Pyramids
        printf("  ");

        // Second Pyramid
        for (int hash = 0; hash < w; hash++)
        {
            printf("#");
        }

        w++;
        x--;
        printf("\n");
    }

}