// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

const unsigned int N = 27;

// Represents a node in a hash table
typedef struct node
{
    char word;
    bool is_word;
    struct node *next[N];

}
node;

// Hash table
node *table;
int ind = 0;
int lower = 96;
int upper = 64;
int apost = 39;
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table;
    int hash_key[strlen(word) - 1];
    ind = 0;

    // Creat hash key in an array and move cursor to final key location
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_key[i] = hash(word);
        if (cursor->next[hash_key[i]] == NULL)
        {
            return false;
        }
        cursor = cursor->next[hash_key[i]];
        ind++;
    }

    // If location is a word return true
    if (cursor->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Hash word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int n;
    if (word[ind] == '\'')
    {
        n = word[ind] - apost;
    }
    else if (islower(word[ind]) == 0)
    {
        n = word[ind] - upper;
    }
    else
    {
        n = word[ind] - lower;
    }

    return n;
}

// Create new node inside of the TRIE
node *create_node(char c)
{
    // Create new node
    node *n = malloc(sizeof(node));
    // Set all next pointers to NULL
    for (int i = 0; i < N; i++)
    {
        n->next[i] = NULL;
    }
    n->word = c;
    n->is_word = false;
    return n;
}

// Insert the next word into the TRIE
void insert_word(node *t, char *word)
{
    node *cursor = t;
    int index;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '\'')
        {
            index = word[i] - apost;
        }
        else
        {
            index = word[i] - lower;
        }

        if (cursor->next[index] == NULL)
        {
            cursor->next[index] = create_node((word[i]));
        }
        cursor = cursor->next[index];
    }
    cursor->is_word = true;
    dict_size++;
    return;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize table
    table = malloc(sizeof(node));
    for (int i = 0; i < N; i++)
    {
        table->next[i] = NULL;
    }
    table->word = '\0';
    table->is_word = false;

    char c;
    int index = 0;
    char new_word[LENGTH];

    while (fread(&c, sizeof(char), 1, file))
    {
        if ((isalpha(c) || c == '\''))
        {
            new_word[index] = c;
            index++;
        }
        else
        {
            new_word[index] = '\0';
            index = 0;
            insert_word(table, new_word);
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int n = dict_size;
    return n;
}

void free_table(node *n)
{
    for (int i = 0; i < N; i++)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            free_table(n->next[i]);
        }
    }
    free(n);
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    free_table(table);
    return true;
}



