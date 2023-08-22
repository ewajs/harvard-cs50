/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"


typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* HashTable[HASHSIZE];
int dictSize;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char wordtocheck[LENGTH + 1];
    int i = 0;
    
    while (word[i] != '\0')
    {
        wordtocheck[i] = tolower(word[i]);
        i++;
    }
    wordtocheck[i] = '\0';
    unsigned int key = hash(wordtocheck) % HASHSIZE;// & 0x1FFFF;
    node* currentWord = HashTable[key];
    // if that entry is empty, no word found
    if (currentWord == NULL)
    {
        return false;
    }
    do
    {
        if (strcmp(currentWord->word,wordtocheck) == 0)
        {
            return true;
        }
        currentWord = currentWord->next;
    }while(currentWord != NULL);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize every entry of the hash table as NULL
    for (int i = 0; i < HASHSIZE; i++)
    {
        HashTable[i] = NULL;
    }
    
    FILE* dict = fopen(dictionary,"rw");
    
    // if something went wrong exit with error
    if (dict == NULL)
    {
        return false;
    }
    dictSize = 0;
    char* word = malloc(sizeof(char) * (LENGTH + 2));
    while (fgets(word, LENGTH + 2, dict))
    {
        word[strlen(word) - 1] = '\0';
        // mask for HASHSIZE
        unsigned int key = hash(word) % HASHSIZE; // & 0x1FFFF; 
        
        // get memory to store current word and copy word to it
        node* currentWord = malloc(sizeof(node));
        currentWord->next = NULL;
        strcpy(currentWord->word, word);
        
       
        if (HashTable[key] == NULL)
        {
            HashTable[key] = currentWord;
        }
        else
        {
            // get pointer to Hash Table entry
            node* next = HashTable[key];
            // add it to the end of the linked list
            while (next->next != NULL)
            {
                next = next->next;
            }
            
            next->next = currentWord;
        }
        dictSize++;
    }
    free(word);
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        node* current = HashTable[i];
        while (current != NULL)
        {
            node* aux;
            aux = current;
            current = current->next;
            free(aux);
        }
    }
    return true;
}

unsigned int hash(char *str)
{
    unsigned long hash = 5381;
    int thisc;

    while ((thisc = *str++))
    {
        hash = ((hash << 5) + hash) + thisc; 
    }
    return hash;
}
