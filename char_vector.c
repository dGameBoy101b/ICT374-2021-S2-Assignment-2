#include "char_vector.h"
#include <stdlib.h>
struct CharVec* createCharVec()
{
	struct CharVec* vec = (struct CharVec*)malloc(sizeof(struct CharVec));
	if (vec == NULL) return NULL;
	vec->count = 0;
	vec->capacity = 1;
	vec->vec = malloc(sizeof(char));
	return vec;
}
void destroyCharVec(struct CharVec** vec)
{
	if (vec == NULL || *vec == NULL) return;
	free((*vec)->vec);
	free(*vec);
	*vec = NULL;
}
int copyCharVec(struct CharVec* dst, struct CharVec* src)
{
	if (dst == NULL || src == NULL) return 0;
	if (!reserveCharVec(dst, src->count)) return 0;
	for (unsigned int i = 0; i < src->count; ++i) dst->vec[i] = src->vec[i];
	dst->count = src->count;
	return 1;
}
char* getEleCharVec(struct CharVec* vec, unsigned int index)
{
	if (vec == NULL || index >= vec->count) return NULL;
	return vec->vec + index;
}
int getStrCharVec(char** str, struct CharVec* vec)
{
	if (str == NULL || vec == NULL) return 0;
	char* cha = realloc(*str, sizeof(char) * (vec->count + 1));
	if (cha == NULL) return 0;
	*str = cha;
	for (unsigned int i = 0; i < vec->count; ++i) (*str)[i] = vec->vec[i];
	(*str)[vec->count] = '\0';
	return 1;
}
int reserveCharVec(struct CharVec* vec, unsigned int cap)
{
	if (vec == NULL) return 0;
	if (cap <= vec->capacity) return 1;
	char* cha = realloc(vec->vec, sizeof(char) * cap);
	if (cha == NULL) return 0;
	vec->vec = cha;
	vec->capacity = cap;
	return 1;
}
int appendEleCharVec(struct CharVec* vec, char c)
{
	if (vec == NULL) return 0;
	if (vec->count + 1 > vec->capacity) if(!reserveCharVec(vec, vec->count + 1)) return 0;
	vec->vec[vec->count] = c;
	++(vec->count);
	return 1;
}
int clearCharVec(struct CharVec* vec)
{
	if (vec == NULL) return 0;
	if (vec->count == 0) return 1;
	char* cha = malloc(sizeof(char));
	if (cha == NULL) return 0;
	free(vec->vec);
	vec->vec = cha;
	vec->count = 0;
	vec->capacity = 1;
	return 1;
}
