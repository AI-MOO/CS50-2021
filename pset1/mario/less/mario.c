#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Hight: ");
    }
    while ( h < 1 | h > 8 );

    int w = 1;
    int x = h;

    // Number of rows
    for (int i = 1; i <= h ; i++)
    {
        // dots behind the hashs
        for (int d = 1; d < x; d++)
        {
            printf(" ");
        }

        // hashs (blocks)
        for (int j = 0; j < w; j++)
        {
            printf ("#");
        }
        x--;
        w++;
        printf("\n");
    }

}