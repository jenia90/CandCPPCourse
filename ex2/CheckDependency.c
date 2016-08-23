/**
 * @file CheckDependency.c
 * @author jenia90
 * @version 1.0
 * @date 25 Aug 2016
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
#include "MyLinkedList.h"

#include <assert.h>
#include <mem.h>

#define CYCLIC_DEPEND "Cyclic dependency\n"
#define NO_CYCLIC_DEPEND "No Cyclic dependency\n"

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 1000
#define MAX_FILENAME 255
#define MAX_CONNECTED_FILES 100
#define MAX_CONNECTED_FILE_STRING 25600

#define NO_FILE_ERROR "Unable to access specified file!\n"
#define INV_ARG_ERROR "Inavlid number of arguments! Please use: CheckDependency <file_name>\n"
#define DELIMITER ","

typedef struct _dependency
{
    char filename[MAX_FILENAME];
    int connectedFiles[MAX_CONNECTED_FILES];
} *dependencyP;

void parseFile(FILE* fp)
{
    assert(fp);
    char fileNames[MAX_LINES][MAX_FILENAME];
    char connectedFiles[MAX_CONNECTED_FILE_STRING];
    char *token;
    dependencyP dependencies[MAX_LINES];
    MyLinkedListP lists[MAX_LINES];

    int i = 0;
    while (fscanf(fp, "%[^:]: %s%*[\n]", *&fileNames[i], connectedFiles) != EOF)
    {
        lists[i] = createList();
        printf("\nfilename: %s\nconnected files: %s\n", fileNames[i], connectedFiles);
        token = strtok(connectedFiles, DELIMITER);

        while (token)
        {
            insertFirst(lists[i], token);
            printf("%s\n", token);
            token = strtok(NULL, DELIMITER);
        }

        printList(lists[i]);

        i++;
    }

}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, INV_ARG_ERROR);
        exit(-1);
    }

    FILE* fp;
    fp = fopen(argv[1], "r");


    if (!fp)
    {
        fprintf(stderr, NO_FILE_ERROR);
        exit(-1);
    }

    parseFile(fp);

    fclose(fp);

    return 0;
}