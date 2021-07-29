#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    float dollars;
    do
    {
        // Prompt the customer's change
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0.0);

    // convert dolars to cents
    int cents = round(dollars * 100);

    // number of coins categories should be returned
    int coins = 0;

    // 25 cents loop
    while (cents >= 25)
    {
        cents = cents - 25;
        coins++;
    }

    // 10 cents loop
    while (cents >= 10)
    {
        cents = cents - 10;
        coins++;
    }

    // 5 cents loop
    while (cents >= 5)
    {
        cents = cents - 5;
        coins++;
    }

    // 1 cent loop
    while (cents >= 1)
    {
        cents = cents - 1;
        coins++;
    }

    // print the number of coins categories
    printf("%i\n", coins);

}