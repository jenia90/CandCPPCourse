/**
 * @file check_dependency.c
 * @author jenia90
 * @version 1.0
 * @date 18 Aug 2016
 *
 * @brief
 * @section DESCRIPTION:
 *
 * Input:
 * Process:
 * Output:
 */

#include <stdio.h>
#include <stdlib.h>


#include <assert.h>

#define CYCLIC_DEPEND "Cyclic dependency\n"
#define NO_CYCLIC_DEPEND "No Cyclic dependency\n"

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 1000
#define MAX_FILENAME 255
#define MAX_CONNECTED_FILES 100

#define DELIMITER ","

typedef struct
{
    char filename[MAX_FILENAME];
    int connectedFiles[MAX_CONNECTED_FILES];
} dependency;

void parseFile(FILE *fp)
{
    assert(fp != NULL);
    char line[MAX_LINE_LENGTH];
    char fileNames[MAX_CONNECTED_FILES * MAX_FILENAME];
    char *token;

    int i = 0;
    dependency dependencies[MAX_LINES];

    do
    {

    } while (*line != EOF);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        exit(-1);
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        exit(-1);
    }

    parseFile(fp);

    fclose(fp);

    return 0;
}