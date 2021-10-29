#include "execute_command.h"
#include "PWDFuncs.h"
#include "change_prompt.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int equalCharVecStr(struct CharVec *vec, const char *str)
{
    int equal = 0;
    struct CharVec *chVec = createCharVecStr(str);
    equal = equalCharVec(vec, chVec);
    destroyCharVec(chVec);
    return equal;
}

int executeSpecial(const struct Command *const com)
{
    if(com == NULL)
    {
        return 0;
    }

    char* str = NULL;
    int res;

    //Note: a check for CD_KEYWORD is in the normal executeCommand function
    //but it wouldn't really do anything if called from a child process. That
    //is OK and in line with the behaviour of the bash shell.
    if(equalCharVecStr(com->path, CD_KEYWORD))
    {
        if(com->args->count >= 2 && !getStrCharVec(&str, getEleCharVecVec(com->args, 1)))
        {
            return 0;
        }

        res = DirectoryWalk(str);

	free(str);
	if (res)
		return 1;
    }

    return 0;
}

void executeCommand(const struct Command*const com)
{
	if (com == NULL)
		exit(-1);
	//check for special commands
	char* str = NULL;
	int res;
	if (equalCharVecStr(com->path, PWD_KEYWORD))
	{
		PrintPWD();
		exit(0);
	}
	if (equalCharVecStr(com->path, CD_KEYWORD))
	{
		res = com->args->count > 1 && getStrCharVec(&str, com->args->vec[1]) && DirectoryWalk(str);
		free(str);
		if (res)
			exit(0);
		exit(-1);
	}
	if (equalCharVecStr(com->path, PROMPT_KEYWORD))
	{
		res = com->args->count > 1 && getStrCharVec(&str, com->args->vec[1]) && changePrompt(str);
		free(str);
		if (res)
			exit(0);
		exit(-1);
	}
printf("exeternal command detected\n");
	if (!getStrCharVec(&str, com->path))
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
		if (!getStrCharVec(&argv[i], com->args->vec[i]))
		{
			free(str);
			exit(-1);
		}
	}
	execvp(str, argv);
	free(str);
	exit(-1);
}
