/**
* mario.c
* Ezequiel Wajs
* ezequiel.wajs@gmail.com
*
* Itsa Mario problem from pset1.
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    // ask for height until allowed value is provided
    do
    {
        printf("Height: ");
        height = GetInt();
    }while(height < 0 || height > 23);
    // print the pyramid
    for(int i = height; i > 0; i--)
    {
        // print the blanks
        for(int j = i - 1; j > 0; j--)
        {
            printf(" ");
        }
        // print the blocks
        for(int k = i - 1; k < height; k++)
        {
            printf("#");
        }
        // print the last block + new line
        printf("#\n");
    }
}
