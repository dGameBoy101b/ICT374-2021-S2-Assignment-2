#include "change_prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_vector.h"

int getPromptPath(char** prompt)
{
	struct CharVec* path = createCharVec();
	char* home = "\0";
	if (PROMPT_PATH[0] == '~')
		home = getenv("HOME");
	if (!reserveCharVec(path, strlen(home) + strlen(PROMPT_PATH)))
		return 0;
	for (char* c = home; *c != '\0'; ++c)
		if (!appendEleCharVec(path, *c))
			return 0;
	char* c;
	if (home[0] == '\0')
		c = PROMPT_PATH;
	else
		c = PROMPT_PATH + 1;
	while (*c != '\0')
	{
		if (!appendEleCharVec(path, *c))
			return 0;
		++c;
	}
	int res = getStrCharVec(prompt, path);
	destroyCharVec(path);
	return res;
}

int changePrompt(const char*const new_prompt)
{
	char* path = NULL;
	if (!getPromptPath(&path))
		return 0;
	FILE* file = fopen(path, "w");
	free(path);
	if (file == NULL)
		return 0;
	fprintf(file, "%s", new_prompt);
	fclose(file);
	return 1;
}

int getPrompt(char** out)
{
	char* path = NULL;
	if (!getPromptPath(&path))
		return 0;
	FILE* file = fopen(path, "r");
	free(path);
	if (file == NULL)
		return 0;
	unsigned int length = 1;
	while (getc(file) != EOF)
		++length;
	if (fseek(file, 0, SEEK_SET))
	{
		fclose(file);
		return 0;
	}
	char* prompt = realloc(*out, sizeof(char) * (length + 1));
	if (prompt == NULL)
	{
		fclose(file);
		return 0;
	}
	int c;
	for (char* it = prompt; prompt < prompt + length; ++it)
	{
		c = getc(file);
		if (c == EOF)
		{
			*it = '\0';
			break;
		}
		*it = c;
	}
	fclose(file);
	prompt[length] = '\0';
	*out = prompt;
	return 1;
}
