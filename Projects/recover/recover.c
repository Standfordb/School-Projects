#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


void find_JPEG(FILE *);
int is_jpeg(uint8_t buffer[]);


int file_idx = 0;
const int BLOCK = 512;
int byte_4[16] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

int main(int argc, char *argv[])
{
    // If incorrect number of command line arguments, quit program with error message
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // If unable to read provided file, quit program with error message
    FILE *image = fopen(argv[1], "r");
    if (image == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }
    // Find and write JPEGs to new files
    find_JPEG(image);

    // Close the image file
    fclose(image);
}

void find_JPEG(FILE *image)
{

    // Initialize output file
    FILE *output = NULL;

    // Iterate over provided file
    uint8_t buffer[sizeof(BYTE) * BLOCK];

    // Read from the provided file
    while (fread(&buffer, sizeof(BYTE), BLOCK, image))
    {
        // If a new jpeg is found
        if (is_jpeg(buffer) == 0)
        {
            // If already writing a file
            if (output != NULL)
            {
                // Close the previous jpeg
                fclose(output);
                file_idx++;

                // Open a new file
                char filename[8];
                sprintf(filename, "%03d.jpg", file_idx);
                output = fopen(filename, "w");

                // Write this block to the new file
                fwrite(&buffer, sizeof(BYTE), BLOCK, output);
            }

            // If no file is open
            else
            {
                // Open a new file to write the next JPEG
                char filename[8];
                sprintf(filename, "%03d.jpg", file_idx);
                output = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK, output);
            }
        }

        // If not a new jpeg and a file is already open
        else if (output != NULL)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK, output);
        }
    }

    // Close the final jpeg file
    fclose(output);
}

int is_jpeg(uint8_t buffer[])
{

    // If first 4 bytes are a match to jpeg format return true
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 0;
    }

    // If not a match to jpeg format return false
    return 1;
}