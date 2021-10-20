#include "char_vector.h"
#include "get_line.h"
#include "change_prompt.h"
#include <stdio.h>

int main(int argc, char** argv, char** env)
{
	char* prompt; //default prompt
	if (!getPrompt(&prompt))
	{
		prompt = PROMPT_DEFAULT;
		changePrompt(PROMPT_DEFAULT);
	}

	struct CharVec* line = createCharVec(); //holds input line
	struct CharVec* EXIT_COM = createCharVecStr("exit"); //the exit command
	while (1)
	{
		printf("%s", prompt);
		getLine(line);
		if (equalCharVec(line, EXIT_COM)) break;
		//continue with command parsing
	}
	destroyCharVec(&line);
	destroyCharVec(&EXIT_COM);
	return 0;
}
