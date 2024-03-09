// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
#define N 26

// Hash table
node *table[N];

int quantity = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        printf("Not enough memory");
        return false;
    }
    cursor = table[index]->next;
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char aux = toupper(word[0]);
    int index = ((int) aux) - 65;
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word_cpy[LENGTH + 1];
    while (fscanf(file, "%45s", word_cpy) == 1)
    {
        int index = hash(word_cpy);
        if (strcmp(word_cpy, "E0F") == 0)
        {
            break;
        }
        else if (table[index] != NULL)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                printf("Not enough memory");
                return false;
            }
            n->next = table[index]->next;
            strcpy(n->word, word_cpy);
            table[index]->next = n;
            quantity++;
        }
        else
        {
            node *n = malloc(sizeof(node));
            node *m = malloc(sizeof(node));
            strcpy(n->word, word_cpy);
            n->next = NULL;
            table[index] = m;
            table[index]->next = n;

            quantity++;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(bool loaded)
{
    // TODO
    if (loaded == false)
    {
        return 0;
    }
    else
    {
        return quantity;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = malloc(sizeof(node));
        if (cursor == NULL)
        {
            printf("Not enough memory");
            free(cursor);
            return false;
        }

        cursor = table[i]->next;
        while (cursor != NULL)
        {
            node *tmp = malloc(sizeof(node));
            if (tmp == NULL)
            {
                printf("Not enough memory");
                free(cursor);
                free(tmp);
                return false;
            }
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
