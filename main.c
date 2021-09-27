#include "char_vector.h"
#include "get_line.h"

int main(int argc, char** argv, char** env)
{
	const char* prompt = ">>> "; //default prompt
	struct CharVec* line = createCharVec(); //holds input line
	struct CharVec* EXIT_COM = createCharVec("exit"); //the exit command
	while (1)
	{
		getLine(line);
		if (equalCharVec(line, EXIT_COM)) break;
		//continue with command parsing
	}
	destroyCharVec(line);
	destroyCharVec(EXIT_COM);
	return 0;
}
