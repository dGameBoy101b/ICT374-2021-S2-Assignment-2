/* File: redirect.c
 * Author: Orlando Molina Santos, ID: 33302151
 * Date: 29 September 2021
 * Purpose: Provides functions to redirect input and output.
 */
 
#include <unistd.h>
#include <fcntl.h>
#include "redirect.h"

int RedirectInput(char *inputFileName)
{
	if(inputFileName == NULL)
		return -1;
	
	int fd;
	fd = open(inputFileName, O_RDONLY);

	if(fd >= 0)
		fd = dup2(fd, STDIN_FILENO);

	return fd;
}

int RedirectOutput(char *outputFileName)
{
	if(outputFileName == NULL)
		return -1;
	
	int fd;
	fd = open (outputFileName, O_WRONLY);
	
	if(fd >= 0)
		fd = dup2(fd, STDOUT_FILENO);
	
	return fd;
}
