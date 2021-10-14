#ifndef TOKENISE_H_INCLUDED
#define TOKENISE_H_INCLUDED

#include "char_vector_vector.h"
#include "char_vector.h"

#define TOKEN_SEP0 ' ' ///The first character used to separate tokens
#define TOKEN_SEP1 '\t' ///The second character used to separate tokens

/** Split the given character vector into a vector of space separated tokens
\param out The vector to fill with tokens
\param str The character vector to split into tokens
\return 0 on failure, 1 on success
*/
int tokenise(struct CharVecVec*const out, const struct CharVec*const str);

#endif // TOKENISE_H_INCLUDED
