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
	printf("%s\n", getenv("PWD"));
}

char *GetCWD()
{
	// Allocate memory for buffer to receive current directory path.
	size_t bufSize = sizeof(char) * 256;
	char *cwd = malloc(bufSize);
	if(cwd == NULL)
	{
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
 * Returns int: 0 on error, 1 on success.
 */
int SetPWDtoCWD()
{
    int success = 0;
    char *cwd = GetCWD();

    if(cwd != NULL)
    {
        //+1 because setenv returns -1 for fail, 0 for success
        success = setenv("PWD", cwd, 1) + 1;
        free(cwd);
    }

    return success;
}

int DirectoryWalk(const char *pathname)
{
	int success = 0;

	if(pathname == NULL)
	{
		pathname = getenv("HOME");
	}

    if(chdir(pathname) == 0 && (success = SetPWDtoCWD()) == 0)
    {
        chdir(getenv("PWD"));
    }

	return success;
}
