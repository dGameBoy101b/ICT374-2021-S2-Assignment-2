struct CharVec {
	char* vec;
	unsigned int count;
};

/** Create a new character vector
\param vec The new character vector
*/
struct CharVec* createCharVec();

/** Destroy the given character vector
\param vec The character vector to destroy
*/
void destroyCharVec(struct CharVec** vec);

/** Get the number of elements in the given character vector
\param vec The character vector to measure
\return The number of elements in the given character vector
*/
unsigned int countCharVec(struct CharVec* vec);

/** Get an element from the given character vector
\param vec The character vector to search
\param index The index at which to find the element
\return A pointer to the found element
*/
char* getEleCharVec(struct CharVec* vec, unsigned int index);

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
