#ifndef COMMAND_PARSE_H_INCLUDED
#define COMMAND_PARSE_H_INCLUDED

#include "job_vector.h"
#include "char_vector_vector.h"

#define JOB_SEP_SEQ ';' ///The sequential job separator
#define JOB_SEP_ASYNC '&' ///The asynchronous job separator
#define COM_SEP_PIPE '|' ///The pipe command separator
#define REDIR_IN '<' ///The input redirection prefix token
#define REDIR_OUT '>' ///The output redirection prefix token

/** Parse the given vector of tokens into a vector of jobs
\param tokens The vector of tokens to parse
\param out The job vector to append the parsed jobs to
\return 0 on failure, 1 on success
*/
int parseCommands(struct JobVec*const out, const struct CharVecVec*const tokens);

#endif // COMMAND_PARSE_H_INCLUDED
