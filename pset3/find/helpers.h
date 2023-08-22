/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Swaps two variables passed by reference.
 */
void swap(int* op1, int* op2);

/**
 * Recursive binary search.
 */
bool binarysearch(int value, int values[], int lower, int upper);
