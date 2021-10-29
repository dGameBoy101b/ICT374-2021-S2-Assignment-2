#pragma once

#define PROMPT_PATH "~/prompt" ///The path at which the prompt is stored
#define PROMPT_DEFAULT ">>> " ///The default prompt used when reading the prompt fails

/** Change the prompt to the given prompt and write it to the home prompt file
\param new_prompt The C-String new prompt to use
\return 0 on failure, 1 on success
*/
int changePrompt(const char*const new_prompt);

/** Read the prompt from the home file
\param out The C-string to read the prompt into
\return 0 on failure, 1 on success
\note Reallocates memory for given out parameter
*/
int getPrompt(char** out);
