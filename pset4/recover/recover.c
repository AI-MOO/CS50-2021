#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int Block_size = 512;

int main(int argc, char *argv[])
{
    // Must be two arguments, 1- code.c: ./recover , 2- raw_file: file.raw
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // opening the file.raw for the purpose of reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Couldn't open the file!\n");
        return 1;
    }

    // opening a file pointer for the purpose of writing
    FILE *output_file = NULL;

    // create a buffer to copy the contents of file.
    BYTE buffer[Block_size];
    // JPG counter
    int jpg_count = 0;

    // while there is data in the raw file which is stored temporary in the buffer! 
    while (fread(&buffer, sizeof(buffer), 1, input_file))
    {
        // check first 4 blocks (512 byte) to ensure that, we have a jpg file!
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //every time we have a new jpg, close the previous output_file ex: (000.jpg) to open a new one below ex: (001.jpg)
            if (jpg_count >= 1)
            {
                fclose(output_file);
            }

            // jpg file name: requires [3] byte for 000 [4] bytes for .jpg [1] byte for \0
            char file_name[8];
            sprintf(file_name, "%03i.jpg", jpg_count);
            output_file = fopen(file_name, "w");
            jpg_count++;
        }

        // writing the contents of buffer on the current opened file for ex: 000.jpg , 001.jpg
        if (jpg_count > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, output_file);
        }

    }

    // closing the files
    fclose(input_file);
    fclose(output_file);

}