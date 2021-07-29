#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


//prototyping
int grade_computer(string text_input);

// main function
int main(void)
{
    // prompt the user to get a text!
    string Text;
    do
    {
        Text = get_string("Text: ");
    }

    // No space must be in the beginning!
    while ((Text[0] == '\0') || (Text[0] == ' '));

    // compute the grade!
    int grade = grade_computer(Text);

}




int grade_computer(string text_input)
{

    int letters_counter = 0, words_counter = 1, sentences_count = 0;
    for (int i = 0, n = strlen(text_input); i < n; i++)
    {
        if (isalpha(text_input[i]))
        {
            letters_counter += 1;
        }

        if (isspace(text_input[i]))
        {
            words_counter += 1;
        }

        if ((text_input[i] == '.') || (text_input[i] == '?') || (text_input[i] == '!'))
        {
            sentences_count += 1;
        }
    }

    // calculating the number of letters and sentences per 100 words
    float L = letters_counter * 100.0 / words_counter;
    float S = sentences_count * 100.0 / words_counter;
    // computing the grade by Coleman-Liau index formula
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Reading level is under Grade 1
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;

    }

    // Reading level is above Grade 16
    if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    // reading levels between Grade 1 & Grade 16 !
    else
    {
        printf("Grade %i\n", index);
        return 0;
    }


}


