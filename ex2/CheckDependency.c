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

#include <assert.h>
#include <mem.h>

#define DEBUG // remove for production.

#define CYCLIC_DEPEND "Cyclic dependency\n"
#define NO_CYCLIC_DEPEND "No Cyclic dependency\n"

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 1000
#define MAX_FILENAME 255
#define MAX_CONNECTED_FILES 100

#define INDEX_NOT_FOUND -1

#define NO_FILE_ERROR "Unable to access specified file!\n"
#define INV_ARG_ERROR "Inavlid number of arguments! Please use: CheckDependency <file_name>\n"
#define DELIMITER ","

typedef struct _Dependency
{
    char fileName[MAX_FILENAME];
    int connectedFilesIndexes[MAX_CONNECTED_FILES];
    char *connectedFileNames[MAX_CONNECTED_FILES];
    int connectedFileCount;

} *DependencyP;

#ifdef DEBUG
// TODO: REMOVE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void printDependencyList(DependencyP dp[], int lCount)
{
    int i, j;
    for (i = 0; i < lCount; i++)
    {
        printf("\nfilename: %s\nconnected files:\n", dp[i]->fileName);
        for(j = 0; j < dp[i]->connectedFileCount; j++)
        {
            printf("%s - %d\n", dp[i]->connectedFileNames[j], dp[i]->connectedFilesIndexes[j]);
        }
    }
}
#endif

/**
 * @brief Gets the index of a given filename in the list of dependency structs
 * @param dp list of dependency structs
 * @param fileName filename to get the index of
 * @return the index of the filename in the dependency array
 */
int indexOf(DependencyP dp[], char *fileName)
{
    int i;

    for(i = 0; i < MAX_LINES; i++)
    {
        if(strcmp(dp[i]->fileName, fileName) == 0)
        {
            return i;
        }
    }

    return INDEX_NOT_FOUND;
}

/**
 * @brief Updates the list of connected files at the given index.
 * @param dp dependency struct array.
 * @param index index of the fileName we want to update its connected file list.
 * @param connectedFiles list of connected files.
 */
void updateConnectedFiles(DependencyP dp[], int index, char *connectedFiles)
{
    char *token = strtok(connectedFiles, DELIMITER);

    while (token)
    {
        dp[index]->connectedFileNames[dp[index]->connectedFileCount++] = token;
        token = strtok(NULL, DELIMITER);
    }
}

/**
 * @brief Reads file line-by-line and populates the dependecny structs list with data
 * @param fp pointer to the file
 * @param dp dependecy struct array
 * @return number of lines containing unique file names.
 */
int parseFile(FILE* fp, DependencyP dp[])
{
    assert(fp && dp);

    char fileName[MAX_FILENAME], connectedFiles[MAX_LINE_LENGTH];
    int lineCount = 0, index;

    while (fscanf(fp, "%[^:]: %s%*[\n]", fileName, connectedFiles) != EOF)
    {
        assert(lineCount <= MAX_LINES);

        if((index = indexOf(dp, fileName)) == -1)
        {
            strcpy(dp[lineCount]->fileName, fileName);
            updateConnectedFiles(dp, lineCount, connectedFiles);
            lineCount++;
        }
        else
        {
            updateConnectedFiles(dp, index, connectedFiles);
        }
    }
    return lineCount;
}

/**
 * @brief Updates the index of each connected file to the respected index in the
 * dependecy structs array
 * @param dp dependecy struct array
 * @param fileCount number of unique fileNames
 */
void updateConnectedFileIndexes(DependencyP dp[], int fileCount)
{
    int i;
    for(i = 0; i < fileCount; i++)
    {
        int j;
        for(j = 0; j < dp[i]->connectedFileCount; j++)
        {
            dp[i]->connectedFilesIndexes[j] = indexOf(dp, dp[i]->connectedFileNames[j]);
        }
    }
}

char *checkForCyclicDependency(DependencyP dp[], int lineCount)
{
}

int main(int argc, char* argv[])
{
    int i, lineCount;
    char *result;
    DependencyP dependencies[MAX_LINES];
    if(argc < 2)
    {
        fprintf(stderr, INV_ARG_ERROR);
        return EXIT_FAILURE;
    }

    for (i = 0; i < MAX_LINES; i++)
    {
        dependencies[i] = (DependencyP)malloc(sizeof(struct _Dependency));
        dependencies[i]->connectedFileCount = 0;
    }

    FILE* fp;
    fp = fopen(argv[1], "r");
    if (!fp)
    {
        fprintf(stderr, NO_FILE_ERROR);
        return EXIT_FAILURE;
    }

    lineCount = parseFile(fp, dependencies);
    fclose(fp);

    updateConnectedFileIndexes(dependencies, lineCount);
    result = checkForCyclicDependency(dependencies, lineCount);
    puts(result);
#ifdef DEBUG
    printDependencyList(dependencies, lineCount);
#endif

    for (i = 0; i < MAX_LINES; i++)
    {
        free(dependencies[i]);
    }

    return EXIT_SUCCESS;
}