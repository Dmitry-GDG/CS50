#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Only one argument is allowed\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    int qty_pic = 50; // qty of pictures
    int nbr_pic; // puctures' number

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Read infile's JPEGHEADER
    uint8_t bf[512];
    char filename[10];
    FILE *outptr;

    nbr_pic = 0;
    while (fread(bf, 1, 512, inptr) > 0)
    {
        if (nbr_pic == 0)
        {
            while (!(bf[0] == 255 && bf[1] == 216 && bf[2] == 255 && (bf[3] >= 224 && bf[3] <= 239)))
            {
                fread(bf, 1, 512, inptr);
            }
        }
        if (bf[0] == 0xff && bf[1] == 0xd8 && bf[2] == 0xff && (bf[3] >= 224 && bf[3] <= 239))
        {
            if (nbr_pic > 0)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03i.jpg", nbr_pic);
            nbr_pic++;
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 5;
            }
        }
        fwrite(bf, 1, 512, outptr);
    }
    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);
    return (0);
}

// call it:
// make recover
// ./recover card.raw