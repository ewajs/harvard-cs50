/**
* initials.c
* Ezequiel Wajs
* ezequiel.wajs@gmail.com
*
* initials problem from pset2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string str = GetString();
    bool lastspace = true;
    // lastspace starts as one to rescue the first letter of the string
    for (int i = 0, n =strlen(str);i < n;i++)
    {
        // if last character was a space, this character must be outputted
        if (lastspace)
        {
            printf("%c", toupper(str[i]));
            lastspace = false;
        }
        // if this character is a space, next character must be outputted
        if (str[i] == ' ')
        {
            lastspace = true;
        }
    }
    printf("\n");
}
