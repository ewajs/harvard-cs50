/**
* caesar.c
* Ezequiel Wajs
* ezequiel.wajs@gmail.com
*
* Caesar Chyper encripting problem from pset2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check for correct no. of arguments
    if (argc != 2)
    {
        printf("This program takes only 1 argument.\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    // check for correct type of argument
    if (k < 1)
    {
        printf("Argument must be a positive integer.\n");
        return 1;
    }
    // as ROT27 = ROT1, take the modulo to simplify computation from hereafter
    k = k % 26;
    // prompt for string to encode   
    string str = GetString();
    
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        // if lowercase, rotate
        if (islower(str[i])) 
        {
            str[i] = (str[i] - 'a' + k) % 26 + 'a';
        }
        // if uppercase, rotate
        else if (isupper(str[i])) 
        {
            str[i] = (str[i] - 'A' + k) % 26 + 'A';
        }
        // if not uppercase or lowercase, do nothing.
    }
    // return encrypted cypher
    printf("%s\n",str);
    // exit succesfully
    return 0;
}
