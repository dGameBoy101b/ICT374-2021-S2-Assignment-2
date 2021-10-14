#include "job.h"
#include "command.h"
#include <stdlib.h>

struct Job* emplaceJob(struct Job* job)
{
	if (job == NULL)
		return NULL;
	job->coms = NULL;
	job->capacity = 0;
	job->count = 0;
	job->async = 0;
	return job;
}

struct Job* createJob()
{
	return emplaceJob(malloc(sizeof(struct Job)));
}

void destroyJob(struct Job* job)
{
	if (job == NULL)
		return;
	for (int i = job->count - 1; i > 0 ; --i)
		destroyCom(job->coms + i);
	free(job->coms);
	free(job);
}

int copyJob(struct Job*const dst, const struct Job*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (!reserveJob(dst, src->count))
		return 0;
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyCom(dst->coms + i, src->coms + i))
			return 0;
	dst->count = src->count;
	dst->async = src->async;
	return 1;
}

int equalJob(const struct Job*const job1, const struct Job*const job2)
{
	if (job1 == NULL || job2 == NULL || job1->count != job2->count || job1->async != job2->async)
		return 0;
	for (unsigned int i = 0; i < job1->count; ++i)
		if (!equalCom(job1->coms + i, job2->coms + i))
			return 0;
	return 1;
}

int reserveJob(struct Job*const job, unsigned int cap)
{
	if (job == NULL)
		return 0;
	if (cap <= job->capacity)
		return 1;
	struct Command* temp = realloc(job->coms, sizeof(struct Command) * cap);
	if (temp == NULL)
		return 0;
	job->coms = temp;
	for (unsigned int i = job->count; i < cap; ++i)
		emplaceCom(job->coms + i);
	job->capacity = cap;
	return 1;
}

int appendEleJob(struct Job*const job, const struct Command* com)
{
	if (job == NULL || com == NULL)
		return 0;
	if (!reserveJob(job, job->count + 1))
		return 0;
	if (!copyCom(job->coms + job->count, com))
		return 0;
	++(job->count);
	return 1;
}

struct Command* getEleJob(const struct Job*const job, unsigned int index)
{
	if (job == NULL || index >= job->count)
		return NULL;
	return job->coms + index;
}

int clearJob(struct Job*const job)
{
	if (job == NULL)
		return 0;
	for (int i = job->count - 1; i > -1; --i)
		destroyCom(job->coms + i);
	free(job->coms);
	emplaceJob(job);
	return 1;
}
