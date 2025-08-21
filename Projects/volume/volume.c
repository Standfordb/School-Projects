// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    //set buffer size to (file size - header) and seek to end of header
    fseek(input, 0, SEEK_END);
    const int BUFFER_SIZE = ftell(input) - 44;
    fseek(input, 44, SEEK_SET);

    //read file to buffer
    int16_t buffer[BUFFER_SIZE / 2];
    fread(&buffer, sizeof(int16_t), BUFFER_SIZE / 2, input);

    //multiply samples by factor
    for (int i = 0; i < BUFFER_SIZE / 2; i++)
    {
        buffer[i] *= factor;
    }

    //write to output file
    fwrite(&buffer, sizeof(int16_t), BUFFER_SIZE / 2, output);

    // Close files
    fclose(input);
    fclose(output);
}
