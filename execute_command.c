#include "execute_command.h"
#include "PWDFuncs.h"
#include "change_prompt.h"
#include <stdlib.h>

void executeCommand(const struct Command*const com)
{
	if (com == NULL)
		exit(-1);
	//check for special commands
	char* str = NULL;
	int res;
	if (equalCharVec(com->path, PWD_KEYWORD)
	{
		PrintPWD();
		exit(0);
	}
	if (equalCharVec(com->path, CD_KEYWORD))
	{
		res = com->args->count < 2 || !getStrCharVec(str, com->args->vec + 1) || !DirectoryWalk(str);
		free(str);
		if (res)
			exit(0);
		exit(-1);
	}
	if (equalCharVec(com->path, PROMPT_KEYWORD))
	{
		res = com->args->count < 2 || !getStrCharVec(str, com->args->vec + 1) || !changePrompt(str);
		free(str);
		if (res)
			exit(0);
		exit(-1);
	}
	if (!getStrCharVec(str, com->path))
		exit(-1);
	char** argv = malloc(sizeof(char*) * (com->args->count + 1));
	if (argv == NULL)
	{
		free(str);
		exit(-1);
	}
	argv[com->args->count] = NULL;
	char* arg = NULL;
	for (unsigned int i = 0; i < com->args->count; ++i)
	{
		argv[i] = NULL;
		if (!getStrCharVec(argv[i], com->args->vec[i]))
		{
			free(str);
			exit(-1);
		}
	}
	execv(str, argv);
	free(str);
	exit(-1);
}
