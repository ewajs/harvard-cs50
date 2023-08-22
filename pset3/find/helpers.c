/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

// these two prototypes have to be here to properly run check50
bool binarysearch(int value, int values[], int lower, int upper);

void swap(int* op1, int* op2);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)
    {
        return false;
    }
    return binarysearch(value, values, 0, n);
}

/**
 * Sorts array of n values with bubble sort.
 */
void sort(int values[], int n)
{
    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                swap(&values[i], &values[i + 1]);
                change = true;        
            }    
        }
        n--;
     }
    return;
}

/**
 * Swaps two variables passed by reference.
 */
void swap(int* op1, int* op2)
{
    int aux;
    aux = *op2;
    *op2 = *op1;
    *op1 = aux;
}

/**
 * Recursive binary search.
 */
bool binarysearch(int value, int values[], int lower, int upper)
{
    int current = (upper + lower) / 2;
    // when upper goes behind lower, search is over with no matches
    if (upper < lower)
    {
        return false;
    }
    // if there's a match, return true along the chain
    if (values[current] == value)
    {
        return true;
    }
    // if gone too long, update upper limit
    else if (values[current] > value)
    {
        upper = current - 1;    
    }
    // if gone too short, update lower limit
    else if (values[current] < value)
    {
        lower = current + 1;    
    }
    // if not found and not over yet, recall the function
    return binarysearch(value, values, lower, upper);
}
