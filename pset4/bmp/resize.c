/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale(int) infile outfile\n");
        return 1;
    }
    

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int scale = atoi(argv[1]);
    
    if (scale < 1 && scale > 100)
    {
        printf("Scale must be a positive integer from 1 to 100\n");
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save current height and width
    int oldWidth = bi.biWidth;
    int oldHeight = abs(bi.biHeight);
    
    // determine padding for original scanlines
    int oldPadding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update outfile BITMAPINFOHEADER
    bi.biWidth = bi.biWidth * scale;
    bi.biHeight = bi.biHeight * scale;
    
    int newH = abs(bi.biHeight);
     // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update outfile BITMAPFILEHEADER
    // (new size = W*H*BytesPerPixel + header + padding bytes
    bf.bfSize = bi.biWidth * newH * sizeof(RGBTRIPLE) + 54 + newH * padding;
    
    // update biSizeImage (remove header
    bi.biSizeImage = bf.bfSize - 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

   
    
    // iterate over infile's scanlines
    for (int i = 0; i < oldHeight; i++)
    {
      
        // go to start of line i
        int linesize = oldWidth * sizeof(RGBTRIPLE) + oldPadding;
        fseek(inptr, 54 + linesize * i, SEEK_SET);
        for(int scaley = 0; scaley < scale; scaley++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int scalex = 0; scalex < scale; scalex++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }


            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            // go back to start of the line
            fseek(inptr, -oldWidth * sizeof(RGBTRIPLE) , SEEK_CUR);
        }
        
       
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
