#include "com_vector.h"
#include <stdlib.h>

struct ComVec* createComVec()
{
	struct ComVec* vec = malloc(sizeof(struct ComVec));
	if (vec == NULL)
		return NULL;
	vec->vec = NULL;
	vec->capacity = 0;
	vec->count = 0;
	return vec;
}

void destroyComVec(struct ComVec* vec)
{
	if (vec == NULL)
		return;
	for (unsigned int i = 0; i < vec->count; ++i)
		destroyCom(vec->vec + i);
	free(vec->vec);
	free(vec);
}

int copyComVec(struct ComVec*const dst, const struct ComVec*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (!reserveComVec(dst, src->count))
		return 0;
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyCom(dst->vec + i, src->vec + i))
			return 0;
	dst->count = src->count;
	return 1;
}

int equalComVec(const struct ComVec*const vec1, const struct ComVec*const vec2)
{
	if (vec1 == NULL || vec2 == NULL || vec1->count != vec2->count)
		return 0;
	for (unsigned int i = 0; i < vec1->count; ++i)
		if (!equalCom(vec1->vec + i, vec2->vec + i))
			return 0;
	return 1;
}

int reserveComVec(struct ComVec*const vec, unsigned int cap)
{
	if (vec == NULL)
		return 0;
	if (cap <= vec->capacity)
		return 1;
	struct Command* temp = realloc(vec->vec, sizeof(struct Command) * cap);
	if (temp == NULL)
		return 0;
	for (unsigned int i = vec->count; i < cap; ++i)
	{
		vec->vec[i].path = NULL;
		vec->vec[i].args = NULL;
		vec->vec[i].input_file = NULL;
		vec->vec[i].output_file = NULL;
		vec->vec[i].input_pipe = NULL;
		vec->vec[i].output_pipe = NULL;
		vec->vec[i].async = 0;
	}
	return 1;
}

int appendEleComVec(struct ComVec*const vec, const struct Command* ele)
{
	if (vec == NULL || ele == NULL)
		return 0;
	if (!reserveComVec(vec, vec->count + 1))
		return 0;
	if (!copyCom(vec->vec + vec->count, ele))
		return 0;
	++(vec->count);
	return 1;
}

struct Command* getEleComVec(const struct ComVec*const vec, unsigned int index)
{
	if (vec == NULL || index >= vec->count)
		return NULL;
	return vec->vec + index;
}

void clearComVec(struct ComVec*const vec)
{
	if (vec == NULL)
		return;
	for (unsigned int i = 0; i < vec->count; ++i)
		destroyCom(vec->vec + i);
	free(vec->vec);
	vec->vec = NULL;
	vec->capacity = 0;
	vec->count = 0;
}
