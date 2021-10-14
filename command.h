#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include "char_vector_vector.h"
#include "char_vector.h"

struct Command
{
	struct CharVec* path; ///The path to search for the command
	struct CharVecVec* args; ///The vector of arguments to use
	struct CharVec* input_file; ///The path to the input file to use (NULL for terminal or pipe)
	struct CharVec* output_file; ///The path to the output file to use (NULL for terminal or pipe)
};

/** Write empty values to the given command
\param com The command to write empty values in
\return The given pointer on success or NULL on failure
\warning Does not properly destroy existing values
\note Should only be used when reserving space for a command
*/
struct Command* emplaceCom(struct Command* com);

/** Create an empty command
\return The new empty command
*/
struct Command* createCom();

/** Destroy the given command
\param com The command to destroy
*/
void destroyCom(struct Command* com);

/** Copy a given command into another given command
\param dst The command to copy into
\param src The command to copy from
\return 0 on failure, 1 on success
\note The input and output pipe members are only copied shallowly
*/
int copyCom(struct Command* dst, const struct Command* src);

/** Check if the given commands are equal
\param com1 A command to compare
\param com2 The other command to compare
\return 1 if equal, 0 if not equal
*/
int equalCom(const struct Command* com1, const struct Command* com2);

/** Clear the given command
\param com The command to clear
\return 0 on failure, 1 on success
*/
int clearCom(struct Command* com);

#endif // COMMAND_H_INCLUDED
