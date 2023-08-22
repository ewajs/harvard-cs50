/**
* vigenere.c
* Ezequiel Wajs
* ezequiel.wajs@gmail.com
*
* Vigenere encripting problem from pset2.
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
    
    string key = argv[1];
    // check for correct type of argument
    // printf("Keyword: %s\n",key);
    int keylength = 0;
    do
    {
        // check all characters for letters only
        if (isalpha(key[keylength]))
        {
            // in the meantime, start converting them to numbers
            key[keylength] = toupper(key[keylength]) - 'A';    
        }
        else
        {
            // if a single character is not a letter, exit with an error
            printf("Argument must be a string of letters only.\n");
            return 1;
        }
        keylength++;
    }while (key[keylength] != '\0');
    // once outside keylength represents no. of characters
    // printf("Number of letters: %i\n", keylength);
    // prompt for string to encode   
    string str = GetString();
    int j = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        // if lowercase, rotate
        if (islower(str[i])) 
        {
            str[i] = (str[i] - 'a' + key[j]) % 26 + 'a';
        }
        // if uppercase, rotate
        else if (isupper(str[i])) 
        {
            str[i] = (str[i] - 'A' + key[j]) % 26 + 'A';
        }
        // the next if will be true if any of the above was true
        if (isalpha(str[i]))
        {
            // if a character got rotated, increase keyword index
            j++;
            // once we reach the end of the keyword, restart
            j = j % keylength;
        }
        // if not uppercase or lowercase, do nothing.
    }
    // return encrypted cypher
    printf("%s\n",str);
    // exit succesfully
    return 0;
}
