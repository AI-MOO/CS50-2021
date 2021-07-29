// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z';
int total_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get a hash index
    int index = hash(word);

    node *cursor = table[index];
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }


    return true;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the dictionary file
    FILE *input_dictionary = fopen(dictionary, "r");
    if (input_dictionary == NULL)
    {
        return false;
    }

    // read a single word from dictionary file every time
    char word[LENGTH + 1];
    while(fscanf(input_dictionary, "%s", word) != EOF)
    {
        // create a new node (n) for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // copy word to a new word !
        strcpy(n->word, dictionary);
        n->next = NULL;

        // get a hassing index
        int index = hash(dictionary);
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            n->next = table[index];
            table[index] = n;
        }
        total_words++;
    }
    fclose(input_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // return the total number of words
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free the linked list
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *temp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }


    return true;
}
