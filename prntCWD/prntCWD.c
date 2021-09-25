/* File: prntCWD.c
 * Author: Orlando Molina Santos
 * Date: 26 September 2021
 * Purpose: Prints the current working directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prntCWD.h"

/* Gets the path of the current working directory.
 * Returns: char* - pointer to a string on the heap containing the current working directory.
 * Remember to free the returned pointer when done.
 */
char *GetCWD()
{
	// Allocate memory for buffer to receive current directory path.
	size_t bufSize = sizeof(char) * 256;
	char *cwd = malloc(bufSize);
	if(cwd == NULL)
	{
		fprintf(stderr, "No memory!\n");
		exit(1);
	}
	
	// Try to get current working directory path.
	// If buffer is too small to receive path, increase size and try again.
	while(getcwd(cwd, bufSize) == NULL)
	{
		bufSize += sizeof(char) * 50;
		cwd = realloc(cwd, bufSize);
		if(cwd == NULL)
		{
			fprintf(stderr, "No memory!\n");
			exit(1);
		}
	}
	
	return cwd;
}

/* Prints the path of the current working directory.
 * stream: pointer to a FILE to print to.
 */
void PrintCWD(FILE *stream)
{
	char *cwd = GetCWD();
	fprintf(stream, "%s\n", cwd);
	free(cwd);
}
