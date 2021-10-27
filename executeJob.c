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

/* Executes special built-in commands that affect the shell.
 * command: a Command struct to execute.
 * returns int: 0 if special commands not executed, or 1 if executed successfully.
 */
int ExecuteSpecial(const struct Command *command)
{
    //Execute the special commands, e.g. to change directory.
    return 0;
}

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

/* Waits for all jobs in the same process group to finish.
 * pgID: the process group ID
 */
void WaitForSeqJob(int pgid)
{
    int status;
    int returnPID = 0;
    pgid = pgid * -1;

    while(returnPID != -1)
    {
        returnPID = waitpid(pgid, &status, 0);
    }
}

int ExecuteJob(const struct Job *job)
{
    Pipe *nextPipe = NULL;
    Pipe prevPipe;
    int pid;
    int pgID = -1;

    prevPipe.read = -1;
    prevPipe.write = -1;

    //Some commands aren't executed in a forked child process.
    if(job->count == 1 && ExecuteSpecial(&(job->coms[0])))
    {
        return 1;
    }

    for(unsigned int i = 0; i < job->count; i++)
    {
        if(i + 1 < job->count && (nextPipe = CreatePipe()) == NULL)
        {
            return 0;
        }

        pid = fork();
        if(pid == -1)
        {
            return 0;
        }

        if(pid == 0)
        {
            RedirectStdinStdout(&prevPipe, nextPipe, &(job->coms[i]));
            //ExecuteCommand(command) goes here
        }

        //Set the process group ID for the job
        if(pgID == -1)
        {
            pgID = pid;
            if(setpgid(pid, 0) == -1)
            {
                return 0;
            }
        }

        //Set the process group for the child process
        if(setpgid(pid, pgID) == -1)
        {
            return 0;
        }

        CloseWriteEnd(nextPipe);
        CloseReadEnd(&prevPipe);

        if(nextPipe != NULL)
        {
            dup2(GetReadEnd(nextPipe), GetReadEnd(&prevPipe));
            CloseReadEnd(nextPipe);
        }
        free(nextPipe);
        nextPipe = NULL;
    }

    if(pgID != -1 && job->async == 0)
    {
        WaitForSeqJob(pgID);
    }

    return 1;
}
