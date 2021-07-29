/*
Convert a plaintext into ciphertext by a key contains 26 characters
Ex. Key: YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  ABCdef,zzz
Ciphertext: YUKfrn,ddd
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//KEY array
int ABC[] = {};

//prototyping
string encrypt(string text);

//main function
int main(int argc, string argv[])
{
    //The program can't start without entering two arguments: ./substitution KEY
    if (argc != 2)
    {
        printf("Usage: ./substitution  key\n");
        return 1;
    }

    //The key must contain 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //only alphabet are accepted as a KEY & No duplicated character
    for (int i = 0; i < 26 ; i++)
    {
        // only alphabet are accepted
        bool x = isalpha(argv[1][i]);
        if (x != true)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // dublicated characters are not accepted
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }


        //store the key in the array as integers Ex. A = 65 , B = 66
        ABC [i] = argv[1][i];


    }

    //propmt the user to enter a plain text
    string plaintext = get_string("plaintext:  ");
    //encrypt the plain text
    string ciphertext = encrypt(plaintext);
    //print the output
    printf("ciphertext: %s\n", ciphertext);
}

// Function: convet plaintext into ciphertext by custom encription key
string encrypt(string text)
{
    int index;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Plaintext conversion: contains(a-z)
        if (islower(text[i]))
        {
            index = (text[i] - 97) % 26;
            text[i] = ABC[index];
            text[i] = tolower(text[i]);
        }
        //Plaintext conversion: contains(A-Z)
        if (isupper(text[i]))
        {
            index = (text[i] - 65) % 26;
            text[i] = ABC[index];
            text[i] = toupper(text[i]);
        }
        //Plaintext: contains anything else!
        else
        {
            text[i] = text[i];
        }


    }
    //return the encrypted plaintext
    string text1 = text;
    return text1;
}





