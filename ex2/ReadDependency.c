#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define NO_FILE_ERROR "Unable to access specified file!\n"
#define INV_ARG_ERROR "Invalid number of arguments!\nPlease use: ReadDependency <dir_path> " \
"<output_file>\n"
#define DELIMITER ","
#define ANG_BRAC '<'
#define QUOTE '"'
#define NON_CAPT_INCL "%*[#include ]"
#define ANG_BRAC_STRING "%[^>]>\n"
#define QUOTE_STRING "%[^\"]\"\n"
#define NON_CAPT_STRING "%*[\n]\n"

#define MAX_FILENAME 255
#define MAX_LINE_LENGTH 1001

void scanFile(FILE *inFile, FILE *outFile)
{
    assert(inFile && outFile);

    bool isFirst = true;
    while(fscanf(inFile, NON_CAPT_INCL) != EOF)
    {
        char fn[MAX_FILENAME];

        switch(fgetc(inFile))
        {
            case ANG_BRAC:
                fscanf(inFile, ANG_BRAC_STRING, fn);
                break;
            case QUOTE:
                fscanf(inFile, QUOTE_STRING, fn);
                break;
            default:
                fscanf(inFile, NON_CAPT_STRING);
                continue;
        }
        if(isFirst)
        {
            fprintf(outFile, " %s", fn);
            isFirst = false;
        }
        else
        {
            fprintf(outFile, ",%s", fn);
        }
    }

    fputs("\n", outFile);
}

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, INV_ARG_ERROR);
        return EXIT_FAILURE;
    }


    DIR *d;
    struct dirent *dir;
    char fn[MAX_FILENAME];
    d = opendir(argv[1]);
    FILE *inFile, *outFile;
    outFile = fopen(argv[2], "a");
    if (d)
    {
        while((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == 0)
            {
                sprintf(fn, "%s\\%s", argv[1], dir->d_name);
                inFile = fopen(fn, "r");
                fprintf(outFile,"%s: ", dir->d_name);
                scanFile(inFile, outFile);
                fclose(inFile);
            }

            printf("%s - %d\n", dir->d_name, dir->d_type);
        }
    }
    fclose(outFile);
}