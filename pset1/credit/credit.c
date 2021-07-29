#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    // get the credit card number
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card <= 0);



    // save the original number as a reference
    long original_card = card;

    // index: refers to the position of digit
    // sum1 = second last digit sequence
    // sum2 = last digit sequence

    int index = 0, sum1 = 0, sum2 = 0, add;
    while (card != 0)
    {
        // Addition of second last digit sequene
        if (index % 2 != 0)
        {
            add = card % 10;
            add = add * 2;
            if (add >= 10)
            {
                sum1 = sum1 + (add % 10 + add / 10);
            }
            else
            {
                sum1 = sum1 + add;
            }
            card = card / 10;
            index++;


        }

        // Addition of  last digit sequene
        else
        {
            add = card % 10;
            sum2 = sum2 + add;
            card = card / 10;
            index++;
        }

    }

    // total sum of both sequence
    int total = sum1 + sum2;

    // if the total Multiples of 10 ==> valid card
    if (total % 10 == 0)
    {

        // American Express validation check
        int start_amex = original_card / pow(10, index - 2);
        if ((index == 15) && (start_amex == 34 || start_amex == 37))
        {
            printf("AMEX\n");
            return 0;
        }


        // MasterCard validation check

        int start_master = original_card / pow(10, index - 2);
        if ((index == 16) && (start_master >= 51 && start_master <= 55))
        {
            printf("MASTERCARD\n");
            return 0;
        }

        // VISA validation check
        int start_visa = original_card / pow(10, index - 1) ;
        if ((index >= 13 && index <= 16) && (start_visa == 4))
        {
            printf("VISA\n");
            return 0;
        }


        printf("INVALID\n");

    }


    // if the total not one of Multiples of 10 ==> invalid card
    else
    {
        printf("INVALID\n");
    }

}

