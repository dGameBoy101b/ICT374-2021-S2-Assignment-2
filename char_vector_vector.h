#ifndef CHAR_VECTOR_VECTOR_H
#define CHAR_VECTOR_VECTOR_H

#include "char_vector.h"

struct CharVecVec {
	struct CharVec** vec; ///The dynamic array of character vectors
	unsigned int count; ///The number of character vectors in this vector
	unsigned int capacity; ///The number of character vectors this vector can hold
};

/** Create an empty vector of character vectors
\return A pointer to the created vector of character vectors (NULL on failure)
*/
struct CharVecVec* createCharVecVec();

/** Destroy the given vector of character vectors
\param vec The vector to destroy
*/
void destroyCharVecVec(struct CharVecVec** vec);

/** Reserve more space in the given vector for the given minimum capacity
\param vec The vector of character vectors to expand
\param cap The minimum required capacity
\return 0 on failure, 1 on success
*/
int reserveCharVecVec(struct CharVecVec*const vec, unsigned int cap);

/** Copy the source vector into the destination vector
\param dst The vector of character vectors to copy into
\param src The vector of character vectors to copy from
\return 0 on failure, 1 on success
*/
int copyCharVecVec(struct CharVecVec*const dst, const struct CharVecVec*const src);

/** Test if the given vectors of character vectors are equal
\param u A vector to compare
\param v The other vector to compare
\return 1 if equal, 0 if not equal
*/
int equalCharVecVec(const struct CharVecVec*const u, const struct CharVecVec*const v);

/** Get an element from the given vector of character vectors
\param vec The vector to search
\param index The index of the element to retrieve
\return A pointer to the found element (NULL if not found)
*/
struct CharVec* getEleCharVecVec(struct CharVecVec*const vec, unsigned int index);

/** Append the given element to the end of the given vector
\param vec The vector to append to the end of
\param ele The character vector to append
\return 0 on failure, 1 on success
*/
int appendEleCharVecVec(struct CharVecVec*const vec, const struct CharVec*const ele);

/** Clear the given vector of all elements
\param vec The vector to clear
\return 0 on failure, 1 on success
*/
int clearCharVecVec(struct CharVecVec*const vec);

#endif // CHAR_VECTOR_VECTOR_H
