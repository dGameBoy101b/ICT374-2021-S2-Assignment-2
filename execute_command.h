#pragma once

#include "command.h"

/** The keyword used to run the print working directory command */
#define PWD_KEYWORD "pwd"

/** The keyword used to run the change directory command */
#define CD_KEYWORD "cd"

/** The keyword used to run the change prompt command */
#define PROMPT_KEYWORD "prompt"

/** Execute the given command as the current process
\param com The command to run
\warning Does not return
\note Process will exit with -1 on failure
*/
void executeCommand(const struct Command*const com);

/** Executes special built-in commands that affect the shell.
 \param com: a Command struct to execute.
 \return int: 0 if special commands not executed, or 1 if executed successfully.
 */
int executeSpecial(const struct Command *const com);
