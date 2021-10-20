#include "char_vector.h"
#include "get_line.h"
#include "tokenise.h"
#include "command_parse.h"
#include "char_vector_vector.h"
#include "job_vector.h"
#include <stdio.h>
#include <signal.h>

int main(int argc, char** argv, char** env)
{
	const char* PROMPT = ">>> "; //default prompt
	
	struct sigaction ignore_action;
	ignore_action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, ignore_action, NULL) || sigaction(SIGQUIT, ignore_action, NULL))
		exit(-1);
	
	struct CharVec* line = createCharVec(); //holds input line
	struct CharVecVec* tokens = createCharVecVec(); //holds space separated tokens
	struct JobVec* jobs = createJobVec(); //holds jobs parsed from command
	struct CharVec* EXIT_COM = createCharVecStr("exit"); //the exit command
	while (1)
	{
		printf("%s", PROMPT);
		getLine(line);
		if (equalCharVec(line, EXIT_COM)) break;
		if (!tokenise(tokens, line))
		{
			printf("Tokenisation failed\n");
			continue;
		}
		if (!parseCommands(jobs, tokens))
		{
			printf("Command parsing failed\n");
			continue;
		}
		for (struct Job* job = jobs->vec; job < jobs->vec + jobs->count; ++job)
		{
			//execute job
		}
	}
	destroyCharVec(line);
	destroyCharVec(EXIT_COM);
	destroyCharVecVec(tokens);
	destroyJobVec(jobs);
	exit(0);
}
