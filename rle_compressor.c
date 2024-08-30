#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Compresses the input file using the Run-Length Encoding (RLE) algorithm.
 *
 * @param input The input file to be compressed.
 * @param output The output file where the compressed data will be written.
 */
void compress(FILE *input, FILE *output)
{
    int count = 1;
    char current, previous;

    previous = fgetc(input);
    while ((current = fgetc(input)) != EOF)
    {
        if (current == previous)
        {
            count++;
        }
        else
        {
            fprintf(output, "%c%d", previous, count);
            count = 1;
            previous = current;
        }
    }

    fprintf(output, "%c%d", previous, count);
}

/**
 * @brief Decompresses a file using Run-Length Encoding (RLE) algorithm.
 *
 * This function reads pairs of characters and counts from the input file and writes the characters to the output file
 * the specified number of times. The input file should be compressed using the RLE algorithm.
 *
 * @param input The input file pointer.
 * @param output The output file pointer.
 */
void decompress(FILE *input, FILE *output)
{
    char character;
    int count;

    while (fscanf(input, "%c%d", &character, &count) == 2)
    {
        for (int i = 0; i < count; i++)
        {
            fputc(character, output);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <mode> <input_file> <output_file>\n", argv[0]);
        fprintf(stderr, "Mode: -c for compress, -d for decompress\n");
        return 1;
    }

    FILE *input = fopen(argv[2], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Error: Cannot open the input file\n");
        return 1;
    }

    FILE *output = fopen(argv[3], "w");
    if (output == NULL)
    {
        fprintf(stderr, "Error: Cannot open the output file\n");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0)
    {
        compress(input, output);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        decompress(input, output);
    }
    else
    {
        fprintf(stderr, "Invalid mode. Use -c for compress or -d for decompress\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fclose(input);
    fclose(output);
    printf("Operation completed successfully.\n");

    return 0;
}