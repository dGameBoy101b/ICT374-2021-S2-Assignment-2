#pragma once

#include "command.h"

/** Expand the wildcards in the paths in the argument list of the given command
\param com The command whose arguments should be expanded
\return 0 on failure, 1 on success
*/
int expandArgPaths(struct Command*const com);
