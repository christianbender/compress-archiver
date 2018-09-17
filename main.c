#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

/*
    main: compresses or extracts jpg-files
*/
int main(int argc, char **args)
{
    char *path;
    char pathOut[20];
    FILE *fileIn, *fileOut;
    int c;
    int i;
    if (argc > 1)
    {
        if (strcmp("-c", args[1]) == 0)
        {
            fileOut = fopen("out", "w+b");
            for (i = 2; i < argc; i++)
            {
                path = args[i];
                fileIn = fopen(path, "r+b");
                if (fileIn == NULL)
                {
                    fprintf(stderr, "Can't open file %s\n", path);
                    continue;
                }
                // printf("%s\n", get_content(fileIn));
                while ((c = fgetc(fileIn)) != EOF)
                {
                    fputc(c, fileOut);
                }
            }
        }
        else if (strcmp("-en", args[1]) == 0)
        {
            fileOut = fopen("out", "w+b");
            int key = atoi(args[2]);
            for (i = 3; i < argc; i++)
            {
                path = args[i];
                fileIn = fopen(path, "r+b");
                if (fileIn == NULL)
                {
                    fprintf(stderr, "Can't open file %s\n", path);
                    continue;
                }
                // printf("%s\n", get_content(fileIn));
                while ((c = fgetc(fileIn)) != EOF)
                {

                    fputc(enc(c, key), fileOut);
                }
            }
        }
        else if (strcmp("-e", args[1]) == 0)
        {
            int counter = 1;
            int begin = 1;
            path = args[2];
            fileIn = fopen(path, "r+b");
            if (fileIn == NULL)
            {
                fprintf(stderr, "Can't open file %s\n", path);
                exit(1);
            }
            sprintf(pathOut, "file%d.jpg", counter);
            fileOut = fopen(pathOut, "w+b");
            while ((c = fgetc(fileIn)) != EOF)
            {
                // fputc(c, fileOut);
                if (c != 255 || begin)
                {
                    fputc(c, fileOut);
                    begin = 0;
                }
                else
                {
                    if ((c = fgetc(fileIn)) != EOF)
                    {
                        if (c == 216)
                        {
                            fclose(fileOut);

                            counter++;
                            sprintf(pathOut, "file%d.jpg", counter);
                            fileOut = fopen(pathOut, "w+b");
                            fputc(255, fileOut);
                            fputc(216, fileOut);
                        }
                        else
                        {
                            fputc(255, fileOut);
                            fputc(c, fileOut);
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else if (strcmp("-de", args[1]) == 0)
        {
            int counter = 1;
            int begin = 1;
            int key = atoi(args[2]);
            path = args[3];
            fileIn = fopen(path, "r+b");
            if (fileIn == NULL)
            {
                fprintf(stderr, "Can't open file %s\n", path);
                exit(1);
            }
            sprintf(pathOut, "file%d.jpg", counter);
            fileOut = fopen(pathOut, "w+b");
            int HEAD1 = dec(255, key);
            int HEAD2 = dec(216, key);
            while ((c = fgetc(fileIn)) != EOF)
            {

                if (c == HEAD1 && !begin)
                {
                    if ((c = fgetc(fileIn)) != EOF)
                    {
                        if (c == HEAD2)
                        {
                            fclose(fileOut);

                            counter += 1;
                            sprintf(pathOut, "file%d.jpg", counter);
                            fileOut = fopen(pathOut, "w+b");
                            fputc(255, fileOut);
                            fputc(216, fileOut);
                        }
                        else
                        {
                            fputc(255, fileOut);
                            int newC = dec(c, key);
                            fputc(newC, fileOut);
                        }
                    }
                    else // catch EOF
                    {
                        fputc(255, fileOut);
                        break;
                    }
                }
                else
                {
                    begin = 0;
                    int newC = dec(c, key);
                    fputc(newC, fileOut);
                }
            }
        }
        else
        {
            /* error case */
            goto ERROR;
        }
        fclose(fileIn);
        fclose(fileOut);
    }
    else
    {
    ERROR:
        fprintf(stderr, "Please use options like: \n");
        fprintf(stderr, "compress -c [file1] [file2] ... [fileN] -- for compressing\n");
        fprintf(stderr, "compress -e [compressed_file] -- for extracting\n");
        fprintf(stderr, "compress -en [KEY >= 0 && KEY <= 255] [file1] [file2] ... [fileN] -- for compressing\n");
        fprintf(stderr, "compress -de [KEY >= 0 && KEY <= 255] [compressed_file] -- for compressing\n");
        exit(1);
    }
    return 0;
}
