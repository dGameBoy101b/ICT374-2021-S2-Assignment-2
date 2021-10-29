#define _POSIX_C_SOURCE 199309L //required to properly use signal handlers

#include "char_vector.h"
#include "get_line.h"
#include "tokenise.h"
#include "command_parse.h"
#include "char_vector_vector.h"
#include "job_vector.h"
#include "executeJob.h"
#include "change_prompt.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handleChild(int sig, siginfo_t* info, void* context)
{
	printf("Child %d exitted with status %d\n", info->si_pid, WEXITSTATUS(info->si_status));
	waitpid(info->si_pid, NULL, 0);
}

int main(int argc, char** argv, char** env)
{
	struct sigaction ignore_action;
	ignore_action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &ignore_action, NULL) || sigaction(SIGQUIT, &ignore_action, NULL))
		exit(-1);

	struct sigaction child_action;
	child_action.sa_sigaction = handleChild;
	if (sigaction(SIGCHLD, &child_action, NULL))
		exit(-1);
	
	char* prompt; //default prompt
	if (!getPrompt(&prompt))
	{
		prompt = PROMPT_DEFAULT;
		if(!changePrompt(PROMPT_DEFAULT)) perror("Failed to create prompt");
	}

	struct CharVec* line = createCharVec(); //holds input line
	struct CharVecVec* tokens = createCharVecVec(); //holds space separated tokens
	struct JobVec* jobs = createJobVec(); //holds jobs parsed from command
	struct CharVec* EXIT_COM = createCharVecStr("exit"); //the exit command
	while (1)
	{
		printf("%s", prompt);
		getLine(line);
		if (equalCharVec(line, EXIT_COM))
			break;
		if (!tokenise(tokens, line))
		{
			perror("Tokenisation failed");
			continue;
		}
		if (!parseCommands(jobs, tokens))
		{
			perror("Command parsing failed");
			continue;
		}
		for (unsigned int i = 0; i < jobs->count; ++i)
		{
			if (!ExecuteJob(jobs->vec[i]))
				perror("Failed to execute a job");
		}
		if (!getPrompt(&prompt))
			exit(-1);
	}
	printf("Exiting...\n");
	destroyCharVec(line);
	destroyCharVec(EXIT_COM);
	destroyCharVecVec(&tokens);
	destroyJobVec(&jobs);
while (waitpid(-1,NULL,0) != -1) {}
	exit(0);
}
