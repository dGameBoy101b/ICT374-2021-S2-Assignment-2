/* File: pipe.h
 * Date: 16 October 2021
 * Author: Orlando Molina Santos, ID: 33302151
 * Purpose: Provides a struct and functions for dealing with pipes.
 */

/* Encapsulates a pipe.
 */
typedef struct
{
    int read;
    int write;
} Pipe;


/* Creates a pipe.
 * Returns: NULL on error, or a Pipe on the heap if successful.
 */
Pipe *CreatePipe();

/* Gets the file descriptor for the read end of a Pipe
 * Returns int: the file descriptor for the read end of the Pipe.
 */
int GetReadEnd(Pipe *pipe);

/* Gets the file descriptor for the write end of a Pipe
 * Returns int: the file descriptor for the write end of the Pipe.
 */
int GetWriteEnd(Pipe *pipe);

/* Closes the read end of a Pipe.
 */
void CloseReadEnd(Pipe *pipe);

/* Closes the write end of a Pipe
 */
void CloseWriteEnd(Pipe *pipe);

/* Checks if the read end of a Pipe is open
 * Returns int: 1 if read end is open, 0 if read end is closed.
 */
int ReadEndOpen(Pipe *pipe);

/* Checks if the write end of a Pipe is open
 * Returns int: 1 if write end is open, 0 if write end is closed.
 */
int WriteEndOpen(Pipe *pipe);




