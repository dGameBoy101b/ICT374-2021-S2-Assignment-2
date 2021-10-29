#include "job.h"
#include "command.h"
#include <stdlib.h>

struct Job* createJob()
{
	struct Job* job = malloc(sizeof(struct Job));
	if (job == NULL)
		return NULL;
	job->coms = NULL;
	job->capacity = 0;
	job->count = 0;
	job->async = 0;
	return job;
}

void destroyJob(struct Job** job)
{
	if (job == NULL || *job == NULL)
		return;
	for (unsigned int i = 0; i < (*job)->count; ++i)
		destroyCom((*job)->coms + i);
	free((*job)->coms);
	free(*job);
	*job = NULL;
}

int copyJob(struct Job*const dst, const struct Job*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (dst->count > src->count)
		for (unsigned int i = src->count; i < dst->count; ++i)
			destroyCom(dst->coms + i);
	if (!reserveJob(dst, src->count))
		return 0;
	if (dst->count < src->count)
		for (unsigned int i = dst->count; i < src->count; ++i)
			dst->coms[i] = createCom();
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyCom(dst->coms[i], src->coms[i]))
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
		if (!equalCom(job1->coms[i], job2->coms[i]))
			return 0;
	return 1;
}

int reserveJob(struct Job*const job, unsigned int cap)
{
	if (job == NULL)
		return 0;
	if (cap <= job->capacity)
		return 1;
	struct Command** temp = realloc(job->coms, sizeof(struct Command*) * cap);
	if (temp == NULL)
		return 0;
	job->coms = temp;
	job->capacity = cap;
	return 1;
}

int appendEleJob(struct Job*const job, const struct Command* com)
{
	if (job == NULL || com == NULL)
		return 0;
	if (!reserveJob(job, job->count + 1))
		return 0;
	job->coms[job->count] = createCom();
	if (!copyCom(job->coms[job->count], com))
		return 0;
	++(job->count);
	return 1;
}

struct Command* getEleJob(const struct Job*const job, unsigned int index)
{
	if (job == NULL || index >= job->count)
		return NULL;
	return job->coms[index];
}

int clearJob(struct Job*const job)
{
	if (job == NULL)
		return 0;
	for (int i = job->count - 1; i > -1; --i)
		destroyCom(job->coms + i);
	free(job->coms);
	job->coms = NULL;
	job->count = 0;
	job->capacity = 0;
	job->async = 0;
	return 1;
}
