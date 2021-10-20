#pragma once

#include "command.h"

/** The keyword used to run the print working directory command */
const struct CharVec*const PWD_KEYWORD = createCharVecStr("pwd");

/** The keyword used to run the change directory command */
const struct CharVec*const CD_KEYWORD = createCharVecStr("cd");

/** The keyword used to run the change prompt command */
const struct CharVec*const PROMPT_KEYWORD = createCharVecStr("prompt");

/** Execute the given command as the current process
\param com The command to run
\warning Does not return
\note Process will exit with -1 on failure
*/
void executeCommand(const struct Command*const com);
