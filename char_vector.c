#include "char_vector.h"
#include <stdlib.h>
#include <string.h>
struct CharVec* createCharVec()
{
	struct CharVec* vec = (struct CharVec*)malloc(sizeof(struct CharVec));
	if (vec == NULL)
		return NULL;
	vec->vec = NULL;
	vec->capacity = 0;
	vec->count = 0;
	return vec;
}
struct CharVec* createCharVecStr(const char*const str)
{
	struct CharVec* vec = (struct CharVec*)malloc(sizeof(struct CharVec));
	if (vec == NULL)
		return NULL;
	unsigned int cap = strlen(str) + 1;
	char* cha = malloc(sizeof(char) * cap);
	if (cha == NULL)
		return NULL;
	vec->count = cap - 1;
	vec->capacity = cap;
	vec->vec = cha;
	for (unsigned int i = 0; i < vec->count; ++i)
		vec->vec[i] = str[i];
	return vec;
}
void destroyCharVec(struct CharVec* vec)
{
	if (vec == NULL)
		return;
	free(vec->vec);
	free(vec);
}
int copyCharVec(struct CharVec*const dst, const struct CharVec* src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (!reserveCharVec(dst, src->count))
		return 0;
	for (unsigned int i = 0; i < src->count; ++i)
		dst->vec[i] = src->vec[i];
	dst->count = src->count;
	return 1;
}
char* getEleCharVec(const struct CharVec*const vec, unsigned int index)
{
	if (vec == NULL || index >= vec->count)
		return NULL;
	return vec->vec + index;
}
int getStrCharVec(char**const str, const struct CharVec*const vec)
{
	if (str == NULL || vec == NULL)
		return 0;
	char* cha = realloc(*str, sizeof(char) * (vec->count + 1));
	if (cha == NULL)
		return 0;
	*str = cha;
	for (unsigned int i = 0; i < vec->count; ++i)
		(*str)[i] = vec->vec[i];
	(*str)[vec->count] = '\0';
	return 1;
}
int reserveCharVec(struct CharVec*const vec, unsigned int cap)
{
	if (vec == NULL)
		return 0;
	if (cap <= vec->capacity)
		return 1;
	char* cha = realloc(vec->vec, sizeof(char) * cap);
	if (cha == NULL)
		return 0;
	vec->vec = cha;
	vec->capacity = cap;
	return 1;
}
int appendEleCharVec(struct CharVec*const vec, char c)
{
	if (vec == NULL)
		return 0;
	if (vec->count + 1 > vec->capacity) if(!reserveCharVec(vec, vec->count + 1))
		return 0;
	vec->vec[vec->count] = c;
	++(vec->count);
	return 1;
}
int clearCharVec(struct CharVec*const vec)
{
	if (vec == NULL)
		return 0;
	if (vec->count == 0)
		return 1;
	free(vec->vec);
	vec->vec = NULL;
	vec->count = 0;
	vec->capacity = 0;
	return 1;
}
int equalCharVec(const struct CharVec*const u, const struct CharVec*const v)
{
	if (u == NULL || v == NULL || u->count != v->count)
		return 0;
	for (unsigned int i = 0; i < u->count; ++i)
		if (u->vec[i] != v->vec[i])
			return 0;
	return 1;
}
