/* File: PWDFuncs.c
 * Author: Orlando Molina Santos
 * Date: 2 October 2021
 * Purpose: Provides functions for changing the current working directory and printing its path.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "PWDFuncs.h"

extern char **environ;

void PrintPWD()
{
	//In theory, this is all that's needed if DirectoryWalk is the only way that the cwd and PWD are changed in the shell.
	printf("%s\n", getenv("PWD"));
}

char *GetCWD()
{
	// Allocate memory for buffer to receive current directory path.
	size_t bufSize = sizeof(char) * 256;
	char *cwd = malloc(bufSize);
	if(cwd == NULL)
	{
		fprintf(stderr, "No memory!\n");
		return NULL;
	}

	// Try to get current working directory path.
	// If buffer is too small to receive path, increase size and try again.
	while(getcwd(cwd, bufSize) == NULL)
	{
		char *temp;
		bufSize += sizeof(char) * 50;

		temp = realloc(cwd, bufSize);

		if(temp == NULL)
		{
			free(cwd);
			cwd = NULL;
			fprintf(stderr, "No memory!\n");
			return NULL;
		}
		else
		{
			cwd = temp;
		}
	}

	return cwd;
}

/* Sets the PWD environment variable to the current working directory.
 * Returns int: -1 on error, 0 on success.
 */
int SetPWDtoCWD()
{
    int success = -1;
    char *cwd = GetCWD();

    if(cwd != NULL)
    {
        success = setenv("PWD", cwd, 1);
        free(cwd);
    }

    return success;
}

int DirectoryWalk(char *pathname)
{
	int success = -1;

	if(pathname == NULL)
	{
		pathname = getenv("HOME");
	}

    if(chdir(pathname) == 0)
    {
        if((success = SetPWDtoCWD()) == -1)
        {
            chdir(getenv("PWD"));
        }
    }

    if(success == -1)
    {
        printf("Could not change directory to:\n%s\n", pathname);
    }

	return success;
}
