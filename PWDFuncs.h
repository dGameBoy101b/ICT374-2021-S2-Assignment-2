/* File: PWDFuncs.h
 * Author: Orlando Molina Santos
 * Date: 2 October 2021
 * Purpose: Provides functions to change the current directory and print its pathname.
 */


/* Prints the PWD of the shell process.
 */
void PrintPWD();

/* Gets the path of the current working directory.
 * Returns char*: NULL if error, otherwise points to a string on the heap containing the current working directory.
 * Remember to free the returned pointer when done.
 */
char *GetCWD();

/* Changes the working directory, and sets the PWD.
 * pathname: the new working directory. If NULL, function will try to change directory to user's HOME directory.
 * Returns int: -1 if directory and PWD can't be changed, 0 on success.
 */
int DirectoryWalk(char *pathname);
