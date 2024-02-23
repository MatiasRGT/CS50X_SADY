// 23/02/24 sady

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// header is used to store all the bytes of the header of input.wav
uint8_t header[44];

// buffer is used to store the bytes of the content of input.wav (What is going to get modified by FACTOR)
int16_t buffer;

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

    float factor = atof(argv[3]); // ascii to float - Used to transform last argument to float value.

    // Copy header from input file to output file
    fread(header, HEADER_SIZE, 1, input);   // takes the bytes from input.wav header
    fwrite(header, HEADER_SIZE, 1, output); // puts the bytes into output.wav header

    // Read samples from input file and write updated data to output file after updating them by FACTOR
    // fetch the WAV sample, And at the same time ask if its valid (Did the file already end?)
    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        buffer = buffer * factor;                    // Transforms WAV sample
        fwrite(&buffer, sizeof(int16_t), 1, output); // Writes the result into output.wav
    }

    // Close files
    fclose(input);
    fclose(output);
}
