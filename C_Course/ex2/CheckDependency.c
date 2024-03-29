/**
 * @file CheckDependency.c
 * @author jenia90
 * @version 1.0
 * @date 25 Aug 2016
 *
 * @brief Program for detection of circular dependencies in specially formated description files
 * @section DESCRIPTION:
 *  This program scans the given description file and after parsing it, checks if the soursce
 *  files described there contain circular dependencies.
 * Input: formated dependency file
 * Process: using DFS algorithm checks if it contains circular dependencies
 * Output: result of the check "Cyclic Dependency" or "No Cyclic Dependency"
 */
#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CYCLIC_DEPEND "Cyclic Dependency\n"
#define NO_CYCLIC_DEPEND "No Cyclic Dependency\n"

#define MAX_LINE_LENGTH 1001
#define MAX_LINES 1000
#define MAX_FILENAME 255
#define MAX_CONNECTED_FILES 100

#define INDEX_NOT_FOUND -1

#define NO_FILE_ERROR "Unable to access specified file!\n"
#define INV_ARG_ERROR "Invalid number of arguments!\nPlease use: CheckDependency <file_name>\n"

#define DELIMITER ","
#define LINE_PARSE_STRING "%[^:]: %s%*[\n]"

#define FILE_NAME_IDX 1
#define FILE_READ_ACCESS "r"

#define MATCHING 0
typedef struct _Dependency
{
    char fileName[MAX_FILENAME];
    int connectedFilesIndexes[MAX_CONNECTED_FILES];
    char connectedFileNames[MAX_CONNECTED_FILES][MAX_FILENAME];
    int connectedFileCount;

} *DependencyP;

#ifdef DEBUG
/**
* @brief function used for debugging. It prints  each filename and the list of connected
* files it has
* @param dp array of dependency struct pointers
* @param lCount number of lines in the scanned file also the number of structs in the array.
*/
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
int indexOf(DependencyP dp[], char *fileName, int lineCount)
{
    assert(dp);

    int i;
    for(i = 0; i < lineCount; i++)
    {
        if(strcmp(dp[i]->fileName, fileName) == 0)
        {
            return i;
        }
    }

    return INDEX_NOT_FOUND;
}

/**
 * Checks if the given filename is already among the connected filenames
 * @param dp Dependency struct pointer
 * @param fileName filename to check
 * @return index of the file if found; -1 otherwise.
 */
int isInConnectedFiles(DependencyP dp, char *fileName)
{
    assert(dp && fileName);

    int i;
    for (i = 0; i < dp->connectedFileCount; ++i)
    {
        if(strcmp(dp->connectedFileNames[i], fileName) == MATCHING)
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
    assert(dp && connectedFiles);

    char *token = strtok(connectedFiles, DELIMITER);
    while (token)
    {
        if(isInConnectedFiles(dp[index], token) == INDEX_NOT_FOUND)
        {
            strcpy(dp[index]->connectedFileNames[dp[index]->connectedFileCount++], token);
        }

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

    // each is spit into 2 variables: filename and the lit of connected files
    while (fscanf(fp, LINE_PARSE_STRING, fileName, connectedFiles) != EOF)
    {
        assert(lineCount <= MAX_LINES); // check that we don't exceed array size.

        // if this file already exists in the list we merge their arrays; create new one otherwise
        if((index = indexOf(dp, fileName, lineCount)) == INDEX_NOT_FOUND)
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
 * @param lineCount number of unique fileNames
 */
void updateConnectedFileIndexes(DependencyP dp[], int lineCount)
{
    int i;
    for(i = 0; i < lineCount; i++)
    {
        int j;
        for(j = 0; j < dp[i]->connectedFileCount; j++)
        {
            // gets the index of each file name in the list
            dp[i]->connectedFilesIndexes[j] = indexOf(dp, dp[i]->connectedFileNames[j], lineCount);
        }
    }
}

/**
 * @brief Initializes and allocates the dependency structs array
 * @param dp dependency struct array
 * @param size number of dependencies to allocate
 */
void allocateDependencyRange(DependencyP dp[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        dp[i] = (DependencyP)malloc(sizeof(*dp[i]));
        dp[i]->connectedFileCount = 0;
    }
}

/**
 * @brief Frees allocated memory of unused dependency range.
 * @param dp dependency struct array
 * @param startIndex start index of unused dependencies
 * @param endIndex end index of unused dependencies
 */
void freeDependencyRange(DependencyP *dp, int startIndex, int endIndex)
{
    int i;
    for (i = startIndex; i < endIndex; i++)
    {
        free(dp[i]);
    }
}

/**
 * @brief Recursive DFS algorithm implementation used for detection of cycles (circular
 * dependencies) in dependency struct array.
 * @param dp array of dependency struct pointer
 * @param curr current dependency struct pointer
 * @param visited array of visited indexes
 * @param visArrSize size of the visited array
 * @param lineCount number of structs in the dependency struct array
 * @return CYCLIC_DEPEND string if there is a cycle; NO_CYCLIC_DEPEND otherwise
 */
char *dfs(DependencyP dp[], DependencyP curr, int visited[], int visArrSize, int lineCount)
{
    assert(dp && curr && visited);
    int i, j;
    char *result = NO_CYCLIC_DEPEND;

    //gets the index of current struct and adds it to the array
    visited[visArrSize++] = indexOf(dp, curr->fileName, lineCount);
    for (i = 0; i < curr->connectedFileCount; i++)
    {
        // iterate over every index in visited array skipping the ones with -1
        for(j = 0; j < visArrSize && curr->connectedFilesIndexes[i] != INDEX_NOT_FOUND; j++)
        {
            // if the specified index wasn't visited yet, we visit it recursively.
            if(curr->connectedFilesIndexes[i] != visited[j])
            {
                result = dfs(dp, dp[curr->connectedFilesIndexes[i]], visited, visArrSize, lineCount);
            }
            // if it was visited that means there's a cycle and we return the appropriate message.
            else
            {
                return CYCLIC_DEPEND;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, INV_ARG_ERROR);
        return EXIT_FAILURE;
    }

    int lineCount;
    DependencyP dependencies[MAX_LINES];

    // allocate memory for each struct pointer
    allocateDependencyRange(dependencies, MAX_LINES);

    // open the file and init file pointer
    FILE* fp;
    fp = fopen(argv[FILE_NAME_IDX], FILE_READ_ACCESS);
    if (!fp)
    {
        fprintf(stderr, NO_FILE_ERROR);
        return EXIT_FAILURE;
    }

    // parse file and get the number of lines in the file
    lineCount = parseFile(fp, dependencies);
    fclose(fp);

    // update the indexes of connected files for each dependency struct
    updateConnectedFileIndexes(dependencies, lineCount);

#ifdef DEBUG
    printDependencyList(dependencies, lineCount);
#endif

    // print the result of Circular Dependency check using DFS algorithm
    int visited[MAX_CONNECTED_FILES];
    puts(dfs(dependencies, dependencies[0], visited, 0, lineCount));

    // free the rest of allocated memory
    freeDependencyRange(dependencies, 0, MAX_LINES);
    return EXIT_SUCCESS;
}
