// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    uint8_t header[HEADER_SIZE];
    int16_t buffer;
    int ifread;
    int ifwrite;
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    ifread = fread(header, 1, 44, input);
    ifwrite = fwrite(header, 1, 44, output);
    if (ifread != ifwrite)
    {
        return (1);
    }

    // TODO: Read samples from input file and write updated data to output file
    ifread = fread(&buffer, 2, 1, input);
    while (ifread > 0)
    {
        buffer *= factor;
        ifwrite = fwrite(&buffer, 2, 1, output);
        if (ifread != ifwrite)
        {
            return (1);
        }
        ifread = fread(&buffer, 2, 1, input);
    }

    // Close files
    fclose(input);
    fclose(output);
}

/* call it:
* make volume
* ./volume input.wav output.wav 2.0 */