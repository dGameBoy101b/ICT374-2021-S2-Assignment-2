#include "char_vector.h"
#include "get_line.h"
#include <stdio.h>

int main(int argc, char** argv, char** env)
{
	const char* PROMPT = ">>> "; //default prompt
	struct CharVec* line = createCharVec(); //holds input line
	struct CharVec* EXIT_COM = createCharVecStr("exit"); //the exit command
	while (1)
	{
		printf(PROMPT);
		getLine(line);
		if (equalCharVec(line, EXIT_COM)) break;
		//continue with command parsing
	}
	destroyCharVec(&line);
	destroyCharVec(&EXIT_COM);
	return 0;
}
