#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//prototyping
string encrypt(string text, int key);

// defining varibales
string plain_text, cipher_text;

// main function
int main(int argc, string argv[])
{
    // Sould include ./caesar #num
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // converting argv[] into integer represets the shift value (key)
    int shift = strtol(argv[1], NULL, 10);

    // prompt the user to enter a plain text
    plain_text = get_string("plaintext:  ");

    // convert the plaintext into a ciphertext
    cipher_text = encrypt(plain_text, shift);
    printf("ciphertext: %s\n", cipher_text);

}


// encryption function
string encrypt(string text, int key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Plaintext contains : a-z
        if (islower(text[i]))
        {
            text[i] = (text[i] - 97 + key) % 26 + 97;

        }

        // Plaintext contains : A-Z
        if (isupper(text[i]))
        {
            text[i] = (text[i] - 65 + key) % 26 + 65;
        }

        // Plaintext contains anything else!
        else
        {
            text[i] = text[i];
        }

    }

    // return the ciphertext !
    cipher_text = text;
    return cipher_text;
}
