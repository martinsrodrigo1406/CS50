// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define FNV_OFFSET 2166136261U
#define FNV_PRIME 16777619U

typedef uint8_t BYTE;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 47697;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int h = hash(word);

    for(node *find = *(table + h); find != NULL; find = (*find).next)
                    {
                        if(strcasecmp(word, (*find).word) == 0)
                        {
                           // printf("Palavra %s é igual a palavra %s\n", word, (*find).word);
                            return true;
                        }
                    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hashN = FNV_OFFSET;
    for (char *p = (char*)word; *p; p++)
    {
        *p = tolower(*p);
        hashN ^= (uint32_t)(unsigned char)(*p);
        hashN *= FNV_PRIME;
    }

    int m = N;
    hashN = hashN % m;
    //printf("%i\n", hashN);
    return hashN;
   // return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char *buffer = malloc(sizeof(char));

    FILE *dic = fopen(dictionary, "r");
    int hashInt = -1;
    int charCounter = 0;

    if(!dic)
    {
        return false;
    }
    else
    {
        node *n = malloc(sizeof(node));
                if(n != NULL)
                {
                    (*n).next = NULL;
                }
                else
                {
                    return false;
                }
        for(int i = 0; i < N; i++)
        {
            table[i] = NULL;
        }

        while(fread(buffer, sizeof(char), 1, dic))
        {
                    if((((int)*buffer >= 97) && ((int)*buffer <= 122)) || ((int)*buffer == 39))
                    {
                        (*n).word[charCounter] = *buffer;
                        charCounter++;
                    }
                    else
                    {
                        if(charCounter != 0)
                        {
                            (*n).word[charCounter] = '\0';
                            hashInt = hash((*n).word);
                            (*n).next = *(table + hashInt);
                            *(table + hashInt) = n;
                            //
                            n = malloc(sizeof(node));
                            charCounter = 0;
                        }

                    }
        }
        free(n);
        free(buffer);
        fclose(dic);
        return true;
    }
    fclose(dic);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int counter = 0;
    for(int i = 0; i < N; i++)
        {
           for(node *c = *(table + i); c != NULL; c = (*c).next)
           {
               counter++;
           }
        }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int c = 0;

    for(int i = 0; i < N; i++)
    {
        while(*(table + i) != NULL)
        {
            node *freeing = *(table + i);
            *(table + i) = (*freeing).next;
            free(freeing);
        }

        c++;
    }

    if(c == N)
    {
        return true;
    }

    return false;
}
