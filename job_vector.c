#include "job_vector.h"
#include <stdlib.h>

struct JobVec* createJobVec()
{
	struct JobVec* v = malloc(sizeof(struct JobVec));
	if (v == NULL)
		return NULL;
	v->vec = NULL;
	v->capacity = 0;
	v->count = 0;
	return v;
}

void destroyJobVec(struct JobVec** v)
{
	if (v == NULL || *v == NULL)
		return;
	for (int i = (*v)->count; i > -1; --i)
		destroyJob((*v)->vec + i);
	free((*v)->vec);
	free(*v);
	*v = NULL;
}

int reserveJobVec(struct JobVec*const v, unsigned int cap)
{
	if (v == NULL)
		return 0;
	if (v->capacity >= cap)
		return 1;
	struct Job** vec = realloc(v->vec, sizeof(struct Job*) * cap);
	if (vec == NULL)
		return 0;
	v->vec = vec;
	/*for (unsigned int i = v->count; i < cap; ++i)
		if (emplaceJob(v->vec + i) == NULL)
			return 0;*/
	v->capacity = cap;
	return 1;
}

int copyJobVec(struct JobVec*const dst, const struct JobVec*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (dst->count > src->count)
		for (unsigned int i = src->count; i < dst->count; ++i)
			destroyJob(dst->vec + i);
	if (!reserveJobVec(dst, src->count))
		return 0;
	if (src->count > dst->count)
		for (unsigned int i = dst->count; i < src->count; ++i)
			dst->vec[i] = createJob();
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyJob(dst->vec[i], src->vec[i]))
			return 0;
	dst->count = src->count;
	return 1;
}

int equalJobVec(const struct JobVec*const vec0, const struct JobVec*const vec1)
{
	if (vec0 == NULL || vec1 == NULL || vec0->count != vec1->count)
		return 0;
	for (unsigned int i = 0; i < vec0->count; ++i)
		if (!equalJob(vec0->vec[i], vec1->vec[i]))
			return 0;
	return 1;
}

struct Job* getEleJobVec(const struct JobVec*const v, unsigned int index)
{
	if (v == NULL || index >= v->count)
		return NULL;
	return v->vec[index];
}

int appendEleJobVec(struct JobVec*const v, const struct Job*const ele)
{
	if (v == NULL || ele == NULL)
		return 0;
	if (!reserveJobVec(v, v->count + 1))
		return 0;
	v->vec[v->count] = createJob();
	if (!copyJob(v->vec[v->count], ele))
		return 0;
	++(v->count);
	return 1;
}

int clearJobVec(struct JobVec*const v)
{
	if (v == NULL)
		return 0;
	for (unsigned int i = 0; i < v->count; ++i)
		destroyJob(v->vec + i);
	free(v->vec);
	v->vec = NULL;
	v->capacity = 0;
	v->count = 0;
	return 1;
}
