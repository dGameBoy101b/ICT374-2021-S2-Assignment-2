/* File: executeJob.c
 * Date: 16 October 2021
 * Author: Orlando Molina Santos, ID: 33302151
 * Purpose: Provides functions to execute jobs from a command line.
 */

#include <stdlib.h>
#include <unistd.h>
#include "executeJob.h"
#include "pipe.h"
#include "fileIORedirect.h"
#include "execute_command.h"

/* Redirects stdin and stdout
 * prevPipe: Pipe to receive input from.
 * nextPipe: Pipe to redirect output to.
 * Pre: Is invoked in a child process.
 * Post: stdin and stdout are redirected to pipes.
 */
void RedirectPipes(Pipe *prevPipe, Pipe *nextPipe)
{
    CloseReadEnd(nextPipe);
    CloseWriteEnd(prevPipe);

    if(WriteEndOpen(nextPipe) && dup2(GetWriteEnd(nextPipe), STDOUT_FILENO) == -1)
    {
        exit(1);
    }
    CloseWriteEnd(nextPipe);

    if(ReadEndOpen(prevPipe) && dup2(GetReadEnd(prevPipe), STDIN_FILENO) == -1)
    {
        exit(1);
    }
    CloseReadEnd(prevPipe);
}

/* Redirects stdin and stdout
 * prevPipe: Pipe to receive input from.
 * nextPipe: Pipe to redirect output to.
 * command: the Command struct to redirect stdin and stdout for.
 * Pre: Is invoked in a child process
 * Post: stdin and stdout are redirected for child process
 */

#include <stdio.h>
#include <sys/wait.h>

void RedirectStdinStdout(Pipe *prevPipe, Pipe *nextPipe, const struct Command *command)
{
    char *fileOutBuf = NULL;
    char *fileInBuf = NULL;

    if(command->input_file != NULL)
    {
        if(getStrCharVec(&fileInBuf, command->input_file) == 0)
        {
            exit(1);
        }

        if(access(fileInBuf, F_OK) == -1)
        {
            printf("Shell: %s is not an existing file\n", fileInBuf);
            exit(1);
        }
    }

    if(command->output_file != NULL && getStrCharVec(&fileOutBuf, command->output_file) == 0)
    {
        exit(1);
    }

    RedirectPipes(prevPipe, nextPipe);

    if(fileInBuf != NULL && RedirectStdin(fileInBuf) == 0)
    {
        exit(1);
    }

    if(fileOutBuf != NULL && RedirectStdout(fileOutBuf) == 0)
    {
        exit(1);
    }
    free(fileInBuf);
    fileInBuf = NULL;
    free(fileOutBuf);
    fileOutBuf = NULL;
}

/* Waits for all jobs in the same process group as caller to finish.
 
void WaitForSeqJob()
{
printf("Waiting for processes in own process group to exit...\n");
    int status;
    int returnPID = 0;

    while(returnPID != -1)
    {
        returnPID = waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		printf("Command failed\n");
    }
}*/

int ExecuteJob(const struct Job *job)
{
	if(job->count == 1 && job->coms[0]->path->count == 2 && job->coms[0]->path->vec[0] == CD_KEYWORD[0] && job->coms[0]->path->vec[1] == CD_KEYWORD[1])
		return executeSpecial(job->coms[0]);

	int pgid = fork();
	if (pgid < 0)
		return 0;
	if (pgid > 0)
	{
		if (!job->async)
			waitpid(pgid, NULL, 0);
		return 1;
	}
        if(setpgid(0, 0) == -1)
		exit(EXIT_FAILURE);
	pgid = getpgrp();

    	Pipe *nextPipe = NULL;
    	Pipe *prevPipe = NULL;
	int pid;
	unsigned int children = 0;


    	for(unsigned int i = 0; i < job->count; i++)
    	{
		if(i + 1 < job->count && (nextPipe = CreatePipe()) == NULL)
			exit(EXIT_FAILURE);

		pid = fork();
		if(pid < 0)
			exit(EXIT_FAILURE);
		if(pid == 0)
		{
		    RedirectStdinStdout(prevPipe, nextPipe, job->coms[i]);
		    executeCommand(job->coms[i]);
		}
		++children;

		CloseWriteEnd(prevPipe);
		CloseReadEnd(prevPipe);
		free(prevPipe);
		prevPipe = NULL;

		CloseWriteEnd(nextPipe);
		prevPipe = nextPipe;
		nextPipe = NULL;
    	}
printf("Job %d has %d children\n",getpid(),children);
	for (unsigned int c = 0; c < children; ++c)
	{
		pid = waitpid(-pgid, NULL, 0);
		if (pid < 0)
			exit(EXIT_FAILURE);
		printf("Job %d claimed command %d\n",getpid(),pid);
	}
	exit(EXIT_SUCCESS);
}
