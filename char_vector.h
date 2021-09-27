struct CharVec {
	char* vec; ///The dynamic array containing all elements
	unsigned int count; ///The number of elements on the vector
	unsigned int capacity; ///The number of elements this vector can currently hold
};

/** Create a new character vector
\return The new character vector (NULL if failed)
*/
struct CharVec* createCharVec();

/** Destroy the given character vector
\param vec The character vector to destroy
*/
void destroyCharVec(struct CharVec** vec);

/** Copy the source character vector into the destination character vector
\param dst The destination character vector to copy into
\param src The source character vector to copy from
\return 0 on failure, 1 on success
*/
int copyCharVec(struct CharVec* dst, struct CharVec* src);

/** Get an element from the given character vector
\param vec The character vector to search
\param index The index at which to find the element
\return A pointer to the found element (NULL if out of range)
*/
char* getEleCharVec(struct CharVec* vec, unsigned int index);

/** Copy the contents of the given character vector into the given C-string
\param str A pointer to the C-string to fill
\param vec The character vector the copy from
\return 0 on failure, 1 on success
*/
int getStrCharVec(char** str, struct CharVec* vec);

/** Reserve at least the given capacity in the given character vector
\param vec The character vector to reserve space for
\param cap The minimum number of elements the given vector must be able to store
\return 0 on failure, 1 on success
*/
int reserveCharVec(struct CharVec* vec, unsigned int cap);

/** Append an element to the given character vector
\param vec The character vector to append to
\param c The value to append
\return 0 on failure, and 1 on success
*/
int appendEleCharVec(struct CharVec* vec, char c);

/** Clear all elements in the given character vector
\param vec The character vector to clear
\return 0 on failure, 1 on success
*/
int clearCharVec(struct CharVec* vec);
