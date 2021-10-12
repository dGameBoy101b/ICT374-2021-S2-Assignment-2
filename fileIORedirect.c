/* File: fileIORedirect.c
 * Author: Orlando Molina Santos, ID: 33302151
 * Date: 29 September 2021
 * Changes: 12 October 2021:
 *      - Opened files are closed after stdin/stdout are redirected.
 *      - Added appropriate permissions for created output files.
 * Purpose: Provides functions to redirect input and output.
 */

#include <unistd.h>
#include <fcntl.h>
#include "fileIORedirect.h"

int RedirectStdin(const char *inputFileName)
{
    int success = 0;
    int fd;

	if((fd = open(inputFileName, O_RDONLY)) == -1)
	{
        return 0;
    }

	if(dup2(fd, STDIN_FILENO) >= 0)
	{
        success = 1;
	}

    close(fd);

	return success;
}

int RedirectStdout(const char *outputFileName)
{
    int success = 0;
	int fd;
	//mode of 0664 is rw-rw-r--, which is what bash shell sets for new output files.
	if((fd = open (outputFileName, O_WRONLY|O_TRUNC|O_CREAT, 0664)) == -1)
	{
        return 0;
	}

	if(dup2(fd, STDOUT_FILENO) >= 0)
	{
        success = 1;
	}

    close(fd);

	return success;
}
