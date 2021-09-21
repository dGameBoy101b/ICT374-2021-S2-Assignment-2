#include "char_vector.h"
#include <stdlib.h>
struct CharVec* createCharVec()
{
	struct CharVec* vec = (struct CharVec*)malloc(sizeof(struct CharVec));
	if (vec == NULL) return;
	vec->count = 0;
	vec->vec = malloc(sizeof(char));
}
void destroyCharVec(struct CharVec** vec)
{
	if (vec == NULL || *vec == NULL) return;
	free((*vec)->vec);
	free(*vec);
	*vec = NULL;
}
unsigned int countCharVec(struct CharVec* vec)
{
	return vec->count;
}
char* getEleCharVec(struct CharVec* vec, unsigned int index)
{
	if (vec == NULL || index >= countCharVec(vec)) return NULL;
	return vec->vec + index;
}
int appendEleCharVec(struct CharVec* vec, char c)
{
	if (vec == NULL) return 0;
	char* cha = realloc(vec->vec, sizeof(char) * (countCharVec(vec) + 2));
	if (cha == NULL) return 0;
	vec->vec = cha;
	vec->vec[vec->count] = c;
	++(vec->count);
	return 1;
}
int clearCharVec(struct CharVec* vec)
{
	if (vec == NULL) return 0;
	if (countCharVec(vec) == 0) return 1;
	char* cha = realloc(vec->vec, sizeof(char));
	if (cha == NULL) return 0;
	vec->vec = cha;
	vec->count = 0;
	return 1;
}
