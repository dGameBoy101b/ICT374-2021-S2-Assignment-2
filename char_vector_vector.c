#include "char_vector_vector.h"
#include <stdlib.h>
struct CharVecVec* createCharVecVec()
{
	struct CharVecVec* vec = malloc(sizeof(struct CharVecVec));
	if (vec == NULL)
		return NULL;
	vec->vec = NULL;
	vec->count = 0;
	vec->capacity = 0;
	return vec;
}
void destroyCharVecVec(struct CharVecVec** v)
{
	if (v == NULL || *v == NULL)
		return;
	for (unsigned int i = 0; i < (*v)->count; ++i)
		destroyCharVec((*v)->vec[i]);
	free((*v)->vec);
	free(*v);
	*v = NULL;
}
int reserveCharVecVec(struct CharVecVec*const v, unsigned int cap)
{
	if (v == NULL)
		return 0;
	if (cap <= v->capacity)
		return 1;
	struct CharVec** cha = realloc(v->vec, sizeof(struct CharVec*) * cap);
	if (cha == NULL)
		return 0;
	v->vec = cha;
	v->capacity = cap;
	return 1;
}
int copyCharVecVec(struct CharVecVec*const dst, const struct CharVecVec*const src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (dst->count > src->count)
		for (unsigned int i = src->count; i < dst->count; ++i)
			destroyCharVec(dst->vec[i]);
	if (!reserveCharVecVec(dst, src->count))
		return 0;
	if (dst->count < src->count)
		for (unsigned int i = dst->count; i < src->count; ++i)
			dst->vec[i] = createCharVec();
	for (unsigned int i = 0; i < src->count; ++i)
		if (!copyCharVec(dst->vec[i], src->vec[i]))
			return 0;
	dst->count = src->count;
	return 1;
}
int equalCharVecVec(const struct CharVecVec*const u, const struct CharVecVec*const v)
{
	if (u == NULL || v == NULL || u->count != v->count)
		return 0;
	for (unsigned int i = 0; i < v->count; ++i)
		if (!equalCharVec(u->vec[i], v->vec[i]))
			return 0;
	return 1;
}
struct CharVec* getEleCharVecVec(struct CharVecVec*const v, unsigned int index)
{
	if (v == NULL || index >= v->count)
		return NULL;
	return v->vec[index];
}
int appendEleCharVecVec(struct CharVecVec*const v, const struct CharVec*const ele)
{
	if (v == NULL || ele == NULL)
		return 0;
	if (!reserveCharVecVec(v, v->count + 1))
		return 0;
	v->vec[v->count] = createCharVec();
	if (!copyCharVec(v->vec[v->count], ele))
		return 0;
	(v->count)++;
	return 1;
}
int clearCharVecVec(struct CharVecVec*const v)
{
	if (v == NULL)
		return 0;
	for (unsigned int i = 0; i < v->count; ++i)
		destroyCharVec(v->vec[i]);
	free(v->vec);
	v->vec = NULL;
	v->capacity = 0;
	v->count = 0;
	return 1;
}
