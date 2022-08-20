#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    // verify correct usage of the function
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Verify the file is actually a .raw file
    char *end = {&argv[1][strlen(argv[1] + 4)]};
    if (strcmp(".raw", end) != 0)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // And now, let's get those JPEGS.
    // First check we can correctly read the file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Initialize our regular blockize
    int BLOCK_SIZE = 512;
    uint8_t buffer[BLOCK_SIZE];

    // Initializing what is needed for file read and write
    int JPEGnum = 0;
    bool w_on_img = false;
    bool first_file = true;
    FILE *img;
    char filename[8];

    // Reading blocks
    while (fread(buffer, 1, BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_file)
            {
                sprintf(filename, "%03i.jpg", JPEGnum);
                img = fopen(filename, "w");
                first_file = false;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", JPEGnum);
                img = fopen(filename, "w");
            }
            JPEGnum++;
            fwrite(buffer, 1, BLOCK_SIZE, img);
            w_on_img = true;
        }
        else
        {
            if (w_on_img)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }
    fclose(infile);
    fclose(img);
    return 0;

}