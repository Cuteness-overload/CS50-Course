// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

//global vars
int count_wrds = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 78;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashed = hash(word);
    node *list = table[hashed];

    while (list != NULL)
    {
        if (strcasecmp(word, list->word) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashed = 0;
    // Using four letters for most words
    // Also using a modulo as I have a table built for 3* the alphabet, so zzzz would fail otherwise
    if (strlen(word) > 4)
    {
        for (int i = 0; i < 4; i++)
        {
            hashed += toupper(word[i]) - 'A';
        }
        hashed = hashed % 65;
        hashed += 13;
    }
    // Smaller words get their own loop and own place in the table
    // Ie: a, to, and, for
    else
    {
        for (int i = 0; i < strlen(word); i++)
        {
            hashed += toupper(word[i]) - 'A';
        }
        hashed = hashed % 13;
    }
    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening the file so we can read it into memory
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    // Scanning tiiiiiimmmeeeee
    char word[LENGTH + 1];
    // Had to figure a way to stop once we reach the end of the dictionnary.
    // EOF to the rescue
    while (fscanf(dic, "%s", word) != EOF)
    {
        node *wrd = malloc(sizeof(node));
        if (wrd == NULL)
        {
            return false;
        }

        // Welp, let's place it somewhere
        strcpy(wrd->word, word);
        wrd->next = NULL;
        //punch it, bop it, hash it
        int hashed = hash(word);
        if (table[hashed] == NULL)
        {
            table[hashed] = wrd;
        }
        else
        {
            wrd->next = table[hashed];
            table[hashed] = wrd;
        }

        // Easier to count the nbr of words here than in the function below
        count_wrds += 1;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count_wrds;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Gotta do it for every bucket
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *buffer = list;
            list = list->next;
            free(buffer);
        }
        if (list == NULL && i == (N-1))
        {
            return true;
        }
    }
    return false;
}
