/**
* greedy.c
* Ezequiel Wajs
* ezequiel.wajs@gmail.com
*
* Greedy problem from pset1.
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    // prompt user for number
    do
    {
        printf("Hi! How much change do you owe?\n");
        change = GetFloat();
    }while(change < 0);
    // typecast and round
    int round_change = round(change*100);
    int coin_quantity = 0;// not needed: , quarters = 0, nickels = 0, dimes = 0, cents = 0;
    coin_quantity = round_change/25 + (round_change%25)/10 + ((round_change%25)%10)/5 + (((round_change%25)%10)%5);
    printf("%i\n",coin_quantity);
}
