#ifndef CHAR_VECTOR_H
#define CHAR_VECTOR_H

struct CharVec {
	char* vec; ///The dynamic array containing all elements
	unsigned int count; ///The number of elements on the vector
	unsigned int capacity; ///The number of elements this vector can currently hold
};

/** Create a new character vector
\return The new character vector (NULL if failed)
*/
struct CharVec* createCharVec();

/** Create a new character vector from a C-string
\param str The C-string to copy character from (excluding terminating '\0')
\return The new character vector (NULL if failed)
*/
struct CharVec* createCharVecStr(const char*const str);

/** Destroy the given character vector
\param vec The character vector to destroy
*/
void destroyCharVec(struct CharVec* vec);

/** Copy the source character vector into the destination character vector
\param dst The destination character vector to copy into
\param src The source character vector to copy from
\return 0 on failure, 1 on success
*/
int copyCharVec(struct CharVec*const dst, const struct CharVec*const src);

/** Get an element from the given character vector
\param vec The character vector to search
\param index The index at which to find the element
\return A pointer to the found element (NULL if out of range)
*/
char* getEleCharVec(const struct CharVec*const vec, unsigned int index);

/** Copy the contents of the given character vector into the given C-string
\param str A pointer to the dynamic C-string to fill
\param vec The character vector the copy from
\return 0 on failure, 1 on success
*/
int getStrCharVec(char**const str, const struct CharVec*const vec);

/** Reserve at least the given capacity in the given character vector
\param vec The character vector to reserve space for
\param cap The minimum number of elements the given vector must be able to store
\return 0 on failure, 1 on success
*/
int reserveCharVec(struct CharVec*const vec, unsigned int cap);

/** Append an element to the given character vector
\param vec The character vector to append to
\param c The value to append
\return 0 on failure, and 1 on success
*/
int appendEleCharVec(struct CharVec*const vec, char c);

/** Clear all elements in the given character vector
\param vec The character vector to clear
\return 0 on failure, 1 on success
*/
int clearCharVec(struct CharVec*const vec);

/** Check if the given character vectors have the same content
\param u A character vector to compare
\param v The other character vector to compare
\return 1 if true, 0 if false
*/
int equalCharVec(const struct CharVec*const u, const struct CharVec*const v);

/** Set the contents of the given character vector to the given C-string
\param vec The character vector to set the contents of
\param str The C-string to copy characters from
\return 0 on failure, 1 on success
*/
int setCharVec(struct CharVec*const vec, const char*const str);

#endif // CHAR_VECTOR_H
