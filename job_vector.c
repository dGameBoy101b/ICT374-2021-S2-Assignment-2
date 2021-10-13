#include "job_vector.h"
#include <stdlib.h>

struct JobVec* emplaceJobVec(struct JobVec* vec)
{
	if (vec == NULL)
		return NULL;
	vec->vec = NULL;
	vec->capacity = 0;
	vec->count = 0;
	return vec;
}

struct JobVec* createJobVec()
{
	return emplaceJobVec(malloc(sizeof(struct JobVec)));
}

void destroyJobVec(struct JobVec* vec)
{
	if (vec == NULL)
		return;
	for (int i = vec->count; i > -1; --i)
		destroyJob(vec->vec + i);
	free(vec->vec);
	free(vec);
}

int reserveJobVec(struct JobVec*const vec, unsigned int cap)
{
	if (vec == NULL)
		return 0;
	if (vec->capacity >= cap)
		return 1;
	struct Job* v = realloc(vec->vec, sizeof(struct Job) * cap);
	if (v == NULL)
		return 0;
	vec->vec = v;
	for (unsigned int i = vec->count; i < cap; ++i)
		if (emplaceJob(vec->vec + i) == NULL)
			return 0;
	vec->capacity = cap;
	return 1;
}

int copyJobVec(struct JobVec*const dst, const struct JobVec*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (!reserveJobVec(dst, src->count))
		return 0;
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyJob(dst->vec + i, src->vec + i))
			return 0;
	dst->count = src->count;
	return 1;
}

int equalJobVec(const struct JobVec*const vec0, const struct JobVec*const vec1)
{
	if (vec0 == NULL || vec1 == NULL || vec0->count != vec1->count)
		return 0;
	for (unsigned int i = 0; i < vec0->count; ++i)
		if (!equalJob(vec0->vec + i, vec1->vec + i))
			return 0;
	return 1;
}

struct Job* getEleJobVec(const struct JobVec*const vec, unsigned int index)
{
	if (vec == NULL || index >= vec->count)
		return NULL;
	return vec->vec + index;
}

int appendEleJobVec(struct JobVec*const vec, const struct Job*const ele)
{
	if (vec == NULL || ele == NULL)
		return 0;
	if (!reserveJobVec(vec, vec->count + 1))
		return 0;
	if (!copyJob(vec->vec + vec->count, ele))
		return 0;
	++(vec->count);
	return 1;
}

int clearJobVec(struct JobVec*const vec)
{
	if (vec == NULL)
		return 0;
	free(vec->vec);
	vec->vec = NULL;
	vec->capacity = 0;
	vec->count = 0;
	return 1;
}
