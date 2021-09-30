#ifndef COM_VECTOR_H_INCLUDED
#define COM_VECTOR_H_INCLUDED

#include "command.h"

struct ComVec
{
	struct Command* vec; ///The dynamic array that hollds all the command elements
	unsigned int capacity; ///The number of elements the vector can hold
	unsigned int count; ///The number of elements the vector is currently holding
};

/** Create an empty command vector
\return The empty command vector
*/
struct ComVec* createComVec();

/** Destroy the given command vector
\param vec The command vector to destroy
*/
void destroyComVec(struct ComVec* vec);

/** Copy the given command vector into the other given command vector
\param dst The command vector to copy into
\param src The command vector to copy from
\return 0 on failure, 1 on success
*/
int copyComVec(struct ComVec*const dst, const struct ComVec*const src);

/** Test if the given commmand vectors are equal
\param vec1 A command vector to compare
\param vec2 The other command vector to compare
\return 1 if equal, 0 if not equal
*/
int equalComVec(const struct ComVec*const vec1, const struct ComVec*const vec2);

/** Expand the capacity of the given command vector to hold at least the given number of elements
\param vec The command vector to expand
\param cap The minimum number of elements to hold
\return 0 on failure, 1 on success
*/
int reserveComVec(struct ComVec*const vec, unsigned int cap);

/** Add the given element onto the end of the given command vector
\param vec The command vector to add onto
\param ele The element to add
\return 0 on failure, 1 on success
*/
int appendEleComVec(struct ComVec*const vec, const struct Command* ele);

/** Get the element in the given command vector at the given index
\param vec The command vector to search
\param index The index at which to search
\return The element at the given index in the given command vector (NULL if not found)
*/
struct Command* getEleComVec(const struct ComVec*const vec, unsigned int index);

/** Clear the given command vector
\param vec The command vector to clear
*/
void clearComVec(struct ComVec*const vec);

#endif // COM_VECTOR_H_INCLUDED
