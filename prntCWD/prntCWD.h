/* File: prntCWD.h
 * Author: Orlando Molina Santos
 * Date: 26 September 2021
 * Purpose: Prints the current working directory.
 */

#include <stdio.h>

/* Gets the path of the current working directory.
 * Returns: char* - pointer to a string on the heap containing the current working directory.
 * Remember to free the returned pointer when done.
 */
char *GetCWD();

/* Prints the path of the current working directory.
 * stream: pointer to a FILE to print to.
 */
void PrintCWD(FILE *stream);
