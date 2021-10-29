#ifndef JOB_VECTOR_H_INCLUDED
#define JOB_VECTOR_H_INCLUDED

#include "job.h"

struct JobVec
{
	struct Job** vec; ///The dynamic vector containing all jobs
	unsigned int capacity; ///The maximum number of jobs this can currently hold
	unsigned int count; ///The number of jobs this is currently holding
};

/** Construct an empty job vector
\return A pointer to the new job vector, or NULL on failure
*/
struct JobVec* createJobVec();

/** Destruct the given job vector
\param vec A pointer to the the job vector to destruct
*/
void destroyJobVec(struct JobVec** vec);

/** Ensure atleast the given number of jobs can be stored in the given job vector
\param vec The job vector to expand
\param cap The minimum capacity required
\return 0 on failure, 1 on success
*/
int reserveJobVec(struct JobVec*const vec, unsigned int cap);

/** Copy the source job vector into the destination
\param dst The destination to copy into
\param src The source to copy from
\return 0 on failure, 1 on success
*/
int copyJobVec(struct JobVec*const dst, const struct JobVec*const src);

/** Compare the given job vectors for value equality
\param vec0 The first job vector to compare
\param vec1 The other job vector to compare
\return 1 if equal, 0 if not equal
*/
int equalJobVec(const struct JobVec*const vec0, const struct JobVec*const vec1);

/** Get an element from the given job vector at the given index
\param vec The job vector to search
\param index The index to search at
\return The job element in the given job vector at the given index, or NULL if index is out of range
*/
struct Job* getEleJobVec(const struct JobVec*const vec, unsigned int index);

/** Append the given element to the given job vector
\param vec The job vector to append to
\param ele The job to append
\return 0 on failure, 1 on success
*/
int appendEleJobVec(struct JobVec*const vec, const struct Job*const ele);

/** Clear the given job vector of elements and allocated memory
\param vec The job vector to clear
\return 0 on failure, 1 on success
*/
int clearJobVec(struct JobVec*const vec);

#endif // JOB_VECTOR_H_INCLUDED
