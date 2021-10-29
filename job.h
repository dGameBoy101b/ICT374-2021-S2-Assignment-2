#ifndef JOB_H_INCLUDED
#define JOB_H_INCLUDED

#include "command.h"

struct Job
{
	struct Command** coms; ///The dynamic array that hollds all the command elements
	unsigned int capacity; ///The number of elements the job can hold
	unsigned int count; ///The number of elements the job is currently holding
	unsigned char async; ///0 if this job should be executed sequentially, 1 if this job should be executed asynchronously
};

/** Create an empty job
\return The empty job
*/
struct Job* createJob();

/** Destroy the given job
\param job The job to destroy
*/
void destroyJob(struct Job** job);

/** Copy the given job into the other given job
\param dst The job to copy into
\param src The job to copy from
\return 0 on failure, 1 on success
*/
int copyJob(struct Job*const dst, const struct Job*const src);

/** Test if the given jobs are equal
\param job1 A job to compare
\param job2 The other job to compare
\return 1 if equal, 0 if not equal
*/
int equalJob(const struct Job*const job1, const struct Job*const job2);

/** Expand the capacity of the given job to hold at least the given number of commands
\param job The job to expand
\param cap The minimum number of elements to hold
\return 0 on failure, 1 on success
*/
int reserveJob(struct Job*const job, unsigned int cap);

/** Add the given command onto the end of the given job
\param job The job to add onto
\param com The element to add
\return 0 on failure, 1 on success
*/
int appendEleJob(struct Job*const job, const struct Command* com);

/** Get the command in the given job at the given index
\param job The job to search
\param index The index at which to search
\return The command at the given index in the given job (NULL if not found)
*/
struct Command* getEleJob(const struct Job*const job, unsigned int index);

/** Clear the given job
\param job The job to clear
\return 0 on failure, 1 on success
*/
int clearJob(struct Job*const job);

#endif // JOB_H_INCLUDED
