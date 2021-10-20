#include "execute_command.h"
#include "PWDFuncs.h"
#include <stdlib.h>

void executeCommand(const struct Command*const com)
{
	if (com == NULL)
		exit(-1);
	//check for special commands
	char* path = NULL;
	if (equalCharVec(com->path, PWD_KEYWORD)
	{
		PrintPWD();
		exit(0);
	}
	if (equalCharVec(com->path, CD_KEYWORD))
	{
		if (com->args->count < 2 || !getStrCharVec(path, com->args->vec + 1) || !DirectoryWalk(path))
			exit(-1);
		exit(0);
	}
	if (equalCharVec(com->path, PROMPT_KEYWORD))
	{
		//change prompt file
		exit(0);
	}
	if (!getStrCharVec(path, com->path))
		exit(-1);
	char** argv = malloc(sizeof(char*) * (com->args->count + 1));
	if (argv == NULL)
		exit(-1);
	argv[com->args->count] = NULL;
	char* arg = NULL;
	for (unsigned int i = 0; i < com->args->count; ++i)
	{
		argv[i] = NULL;
		if (!getStrCharVec(argv[i], com->args->vec[i]))
			exit(-1);
	}
	execv(path, argv);
	exit(-1);
}
