/* File: pipe.c
 * Date: 16 October 2021
 * Author: Orlando Molina Santos, ID: 33302151
 * Purpose: Provides a struct and functions for dealing with pipes.
 */

#include <unistd.h>
#include "pipe.h"
#include <stdlib.h>

Pipe *CreatePipe()
{
    int tempPipe[2];

    Pipe *p = malloc(sizeof(Pipe));
    if(p == NULL)
    {
        return NULL;
    }

    if(pipe(tempPipe) == 0)
    {
        p->read = tempPipe[0];
        p->write = tempPipe[1];
    }
    else
    {
        free(p);
        p = NULL;
    }

    return p;
}

int GetReadEnd(Pipe *pipe)
{
    if(pipe == NULL)
    {
        return -1;
    }

    return pipe->read;
}

int GetWriteEnd(Pipe *pipe)
{
    if(pipe == NULL)
    {
        return -1;
    }

    return pipe->write;
}

void CloseReadEnd(Pipe *pipe)
{
    if(pipe != NULL && pipe->read != -1)
    {
        close(pipe->read);
        pipe->read = -1;
    }
}

void CloseWriteEnd(Pipe *pipe)
{
    if(pipe != NULL && pipe->write != -1)
    {
        close(pipe->write);
        pipe->write = -1;
    }
}

int ReadEndOpen(Pipe *pipe)
{
    if(pipe == NULL)
    {
        return 0;
    }

    return (pipe->read >= 0);
}

int WriteEndOpen(Pipe *pipe)
{
    if(pipe == NULL)
    {
        return 0;
    }

    return (pipe->write >= 0);
}
