/**
 * @file ReadDependency.c
 * @author jenia90
 * @version 1.0
 * @date 25 Aug 2016
 *
 * @brief Program for scanning source code files and building a list of dependency for each file
 * @section DESCRIPTION:
 *  Given a directory and output file, it scans each source code file in the directory and builds
 *  a dependency list in the output file.
 * Input: directory to scan and output file
 * Process: scans each files' #include lines and builds a list of dependencies for this file in
 * the output file
 * Output: a file containing dependencies for each of the files in the directory
 */

#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define NO_FILE_ERROR "Unable to access specified file\\directory!\n"
#define INV_ARG_ERROR "Invalid number of arguments!\nPlease use: ReadDependency <dir_path> " \
"<output_file>\n"

#define FILEPATH_STRING "%s/%s"
#define FILENAME_STRING "%s: "
#define DELIMITER ","
#define ANG_BRAC '<'
#define QUOTE '"'
#define NON_CAPT_INCL "%*[#include ]"
#define ANG_BRAC_STRING "%[^>]>\n"
#define QUOTE_STRING "%[^\"]\"\n"
#define NON_CAPT_STRING "%*[\n]\n"
#define FIRST_INCL " %s"
#define NON_FIRST_INCL ",%s"
#define LINE_BREAK "\n"

#define MAX_FILENAME 255
#define MAX_LINE_LENGTH 1001

/**
 * @brief Scans the input file and writes all files in the #include section to the output file
 * @param inFile input file pointer
 * @param outFile output file pointer
 */
void scanFile(FILE *inFile, FILE *outFile)
{
    assert(inFile && outFile);

    // boolean for condition when we just begin scanning the included files
    bool isFirst = true;

    // foreach include we scan it into the output file separated by commas
    while(fscanf(inFile, NON_CAPT_INCL) != EOF)
    {
        char fn[MAX_FILENAME];

        // get the type of include declaration (with quote or angle bracket)
        switch(fgetc(inFile))
        {
            case ANG_BRAC:
                fscanf(inFile, ANG_BRAC_STRING, fn);
                break;
            case QUOTE:
                fscanf(inFile, QUOTE_STRING, fn);
                break;
            default:
                // skip every line that is not #include
                fscanf(inFile, NON_CAPT_STRING);
                continue;
        }
        // if it's the first #include we don't add comma in front of it
        if(isFirst)
        {
            fprintf(outFile, FIRST_INCL, fn);
            isFirst = false;
        }
        else
        {
            fprintf(outFile, NON_FIRST_INCL, fn);
        }
    }


    fputs(LINE_BREAK, outFile);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, INV_ARG_ERROR);
        return EXIT_FAILURE;
    }

    DIR *d;
    struct dirent *dir;
    char fn[MAX_FILENAME];

    // get directory pointer from cmdline args
    d = opendir(argv[1]);
    FILE *inFile, *outFile;

    // get output file from cmdline args with write permission.
    outFile = fopen(argv[2], "w");
    if(!outFile)
    {
        fprintf(stderr, NO_FILE_ERROR);
        return EXIT_FAILURE;
    }
    if (d)
    {
        // for every listing in the directory we check if its a file and then process is.
        while((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == 0)
            {
                // gets full path of the file
                sprintf(fn, FILEPATH_STRING, argv[1], dir->d_name);
                inFile = fopen(fn, "r");
                if(!inFile)
                {
                    fprintf(stderr, NO_FILE_ERROR);
                    return EXIT_FAILURE;
                }

                // prints the name of the file being processed
                fprintf(outFile, FILENAME_STRING, dir->d_name);
                scanFile(inFile, outFile);

                // close current input file
                fclose(inFile);
            }
        }
    }
    else
    {
        fprintf(stderr, NO_FILE_ERROR);
        return EXIT_FAILURE;
    }
    //close output file and directory
    fclose(outFile);
    closedir(d);

    return EXIT_SUCCESS;
}