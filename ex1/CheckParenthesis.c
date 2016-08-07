/**
 * @file CheckParenthesis.c
 * @author jenia90
 * @version 1.0
 * @date 11 Aug 2016
 *
 * @brief Program to check parenthesis balancing in a given file.
 * @section DESCRIPTION:
 * This program scans a text file for parenthesis balancing valiolations.
 * Input: Text file.
 * Process: Scanning the text char-by-char and checking the parenthesis order.
 * Output: result of the validation: 'ok' if successful; 'bad structure' otherwise.
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5000 // max parenthesis count

#define ERROR_MSG "bad structure\n"
#define SUCCESS_MSG "ok\n"
#define ARG_ERROR "Please supply a file!\nusage: CheckParenthesis <file name>\n"
#define IO_ERROR "Error! trying to open the file <file name>\n"

#define ERROR_CODE -1

/**
 * Reads the given file char-by-char and checks the balancing of parenthesis expressions.
 * @param pFile the file to scan.
 * @return 0 if successful; -1 otherwise.
 */
int parenthesisCounter(FILE *pFile)
{
    int top = -1; // initial topmost index in the stack
    char c, s[MAX_SIZE]; // c is for current char and s is our bracket stack
    bool error = false;

    /* while not end-of-file we check if we are getting an openning bracket or closing one.
     * If we get openning bracket we add it to the end of our "stack" and if its a closing bracket we do the following:
     * Check if last inserted bracket was of same type, if yes we decrement the "stack" size.
     * In case of no, we set the error variable to 'true' which will end the program with a 'bad structure' code.
     */
    while ((c = (char) fgetc(pFile)) != EOF && !error)
    {
        if(c == '(' || c == '[' || c == '{' || c == '<')
            s[++top] = c;

        else
        {
            switch(c) {
                case ')':
                    if (s[top] == '(')
                        top--;
                    else {
                        error = true;
                    }
                    break;
                case ']':
                    if (s[top] == '[')
                        top--;
                    else {
                        error = true;
                    }
                    break;
                case '}':
                    if (s[top] == '{')
                        top--;
                    else {
                        error = true;
                    }
                    break;
                case '>':
                    if (s[top] == '<')
                        top--;
                    else {
                        error = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    fclose(pFile);

    // if error occured we print error msg and end the program with an error code.
    if (error)
    {
        printf("%s\n", ERROR_MSG);
    }

    // print success message and return success code.
    printf("%s\n", SUCCESS_MSG);
}

/**
 * Main function
 * @param argc command-line argument count.
 * @param argv command-line argument array.
 * @return 0 if run was successful; -1 if exited with 'bad structure' error; -2 if crashed.
 */
int main(int argc, char* argv[])
{
    // check validity of passed in parameters.
    if (argc != 2)
    {
        printf("%s\n", ARG_ERROR);
        return ERROR_CODE;
    }

    FILE* pFile;
    pFile = fopen(argv[1], "r");

    if (pFile == NULL)
    {
        printf("%s\n", IO_ERROR);
        return ERROR_CODE;
    }

    parenthesisCounter(pFile);

    return 0;
}
