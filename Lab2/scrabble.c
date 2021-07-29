#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }


}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int sum = 0, index, registered_point;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // converting every letter to uppercase since A=a...Z=z
        if (islower(word[i]))
        {
            word[i] = toupper(word[i]);
        }
        // let other characters as they are!.
        else
        {
            word[i] = word[i];
        }

        // convrt every letter into its real registered_point in scrabble game!
        if ((word[i] >= 'A') && (word[i] <= 'Z'))
        {
            index = word[i] - 65;
            registered_point = POINTS[index];
            sum = sum + registered_point;
        }
    }

    // return the total score!
    return sum;
}
