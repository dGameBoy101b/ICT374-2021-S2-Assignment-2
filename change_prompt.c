#include "change_prompt.h"
#include <stdio.h>

int changePrompt(const char*const new_prompt)
{
	FILE* file = fopen(PROMPT_PATH, "w");
	if (file == NULL)
		return 0;
	fprintf(file, "%s", new_prompt);
	fclose(file);
	return 1;
}

int getPrompt(char** out)
{
	FILE* file = fopen(PROMPT_PATH, "r");
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
