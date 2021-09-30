#include "char_vector_vector.h"
#include <stdlib.h>
struct CharVecVec* createCharVecVec()
{
	struct CharVecVec* vec = malloc(sizeof(struct CharVecVec));
	if (vec == NULL)
		return NULL;
	struct CharVec* cha = malloc(sizeof(struct CharVec));
	if (cha == NULL)
	{
		free(vec);
		return NULL;
	}
	vec->vec = cha;
	vec->count = 0;
	vec->capacity = 1;
	return vec;
}
void destroyCharVecVec(struct CharVecVec* vec)
{
	if (vec == NULL)
		return;
	for (unsigned int i = 0; i < vec->count; ++i)
		destroyCharVec(vec->vec + i);
	free(vec->vec);
	free(vec);
	vec = NULL;
}
int reserveCharVecVec(struct CharVecVec*const vec, unsigned int cap)
{
	if (vec == NULL)
		return 0;
	if (cap <= vec->capacity)
		return 1;
	struct CharVec* cha = realloc(vec->vec, sizeof(struct CharVec) * cap);
	if (cha == NULL)
		return 0;
	vec->vec = cha;
	for (unsigned int i = vec->count; i < cap; ++i)
	{
		(vec->vec + i)->vec = NULL;
		(vec->vec + i)->capacity = 0;
		(vec->vec + i)->count = 0;
	}
	vec->capacity = cap;
	return 1;
}
int copyCharVecVec(struct CharVecVec*const dst, const struct CharVecVec*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (!reserveCharVecVec(dst, src->count))
		return 0;
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyCharVec(dst->vec + i, src->vec + i))
			return 0;
	dst->count = src->count;
	return 1;
}
int equalCharVecVec(const struct CharVecVec*const u, const struct CharVecVec*const v)
{
	if (u == NULL || v == NULL || u->count != v->count)
		return 0;
	for (unsigned int i = 0; i < v->count; ++i)
		if (!equalCharVec(u->vec + i, v->vec + i))
			return 0;
	return 1;
}
struct CharVec* getEleCharVecVec(struct CharVecVec*const vec, unsigned int index)
{
	if (vec == NULL || index >= vec->count)
		return NULL;
	return vec->vec + index;
}
int appendEleCharVecVec(struct CharVecVec*const vec, const struct CharVec*const ele)
{
	if (vec == NULL || ele == NULL)
		return 0;
	if (!reserveCharVecVec(vec, vec->count + 1))
		return 0;
	if (!copyCharVec(vec->vec + vec->count, ele))
		return 0;
	(vec->count)++;
	return 1;
}
int clearCharVecVec(struct CharVecVec*const vec)
{
	if (vec == NULL)
		return 0;
	struct CharVec* cha = malloc(sizeof(struct CharVec));
	if (cha == NULL)
		return 0;
	for (unsigned int i = 0; i < vec->count; ++i)
		destroyCharVec(vec->vec + i);
	free(vec->vec);
	vec->vec = cha;
	vec->capacity = 1;
	vec->count = 0;
	return 1;
}
