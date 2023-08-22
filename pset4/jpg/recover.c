/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 512

int main(int argc, char* argv[])
{
    uint8_t block[BLOCKSIZE];
    
    // create and initialize pointer to card image
    FILE* infile = fopen("card.raw", "r");
    
    // create pointer to destination JPEG (will be initialized many times)
    FILE* outfile = NULL;
    int imageNo = 0;
    char fileName[8];
    while (!feof(infile))
    {
        int sizeread = fread(block, sizeof(uint8_t), BLOCKSIZE, infile);
        if (sizeread != BLOCKSIZE)
        {
            break;
        }
        
        // if found a new image
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // if this is the first, skip this part
            if (imageNo != 0)
            {
                // close the last one
                fclose(outfile);  
            }
            // update name
            sprintf(fileName,"%03d.jpg",imageNo);
            // create new file
            outfile = fopen(fileName, "w");
            // increase image counter for next one
            imageNo++;
            // save the line
            fwrite(block, sizeof(uint8_t), BLOCKSIZE, outfile);
        }
        // else, still in the same image
        else if (outfile != NULL)
        {
            // simply add it to current file
            fwrite(block, sizeof(uint8_t), BLOCKSIZE, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}
