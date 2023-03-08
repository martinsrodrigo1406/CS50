// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
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

    BYTE *header = malloc(sizeof(BYTE) * HEADER_SIZE);
    SAMPLE *sample = malloc(sizeof(SAMPLE));

    // TODO: Copy header from input file to output file
    fread(header, 44, 1, input);
    fwrite(header, 44, 1, output);


    // TODO: Read samples from input file and write updated data to output file
    size_t bytesRead = 0;

    while((bytesRead = fread(sample, sizeof(SAMPLE), 1, input)) > 0)
    {
        *sample *= factor;
        fwrite(sample, sizeof(SAMPLE), 1, output);
    }
    free(header);
    free(sample);

    // Close files
    fclose(input);
    fclose(output);
}
