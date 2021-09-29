#ifndef GET_LINE_H_INCLUDED
#define GET_LINE_H_INCLUDED

#include "char_vector.h"

/** Get a line from standard input
\param v The character vector to fill with the retrieved line
\return 0 on failure, 1 on success
\note Blocks until a newline or end of file character has been read
*/
int getLine(struct CharVec* v);

#endif // GET_LINE_H_INCLUDED
