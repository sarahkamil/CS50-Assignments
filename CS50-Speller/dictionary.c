// Implements a dictionary's functionality

#include <stdbool.h>
#include <unistd.h>
#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;
int num_words = 0;
bool loaded = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *current_node = table[index];
    while(current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }
        current_node = current_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        unsigned int index = ((unsigned int) word[i]);
        sum += index;
    }
    return sum % N;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        printf("Your file can't be opened.\n");
        return false;
    }

    char array[LENGTH + 1];
    while(fscanf(dictionary_file, "%s", array) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        num_words++;

        strcpy(n->word, array);
        unsigned int index = hash(array);
        n->next = table[index];
        table[index] = n;
    }
    fclose(dictionary_file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return num_words;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            node *tmp = current->next;
            free(current);
            current = tmp;
        }
    }

    return true;
}
